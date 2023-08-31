/**
 * @file RegexMatchWriter.c
 *
 * Definition of internal `struct RegexMatchWriter` and implementation
 * of associated functions
 */

#include <errno.h>
#include <fcntl.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "posix-regex/RegexMatchWriter.h"
#include "posix-regex/macros.h"

/**
 * @struct RegexMatchWriter
 * @brief Internal struct behind opaque type `RegexMatchWriter`
 */
struct RegexMatchWriter {
	/** @brief Compiled regex pattern to match */
	regex_t pattern;

	/** @brief Start address of the search file's mapped memory */
	char * file_start;

	/** @brief End address of the search file's mapped memory */
	char * file_end;
	
	/** @brief Cursor address within file's mapped memory */
	char * pos;
	
	/** @brief Delimiter for separating match outputs */
	char * delim;
	
	/** @brief Length of delimiter string */
	size_t delim_len;
	
	/** @brief File descriptor for the search file */
	int in_fd;

	/** @brief File descriptor for writing output */
	int out_fd;
};

/**
 * @brief
 * Compiles `pattern` member of `RegexMatchWriter` from `regex`
 * string argument (static function)
 *
 * @param writer Pointer to valid `RegexMatchWriter`
 * @param regex Regex string to compile
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 * @return `1` on success, `0` on failure
 */
static int
RegexMatchWriter_REGCOMP(
	RegexMatchWriter * writer,
	const char * regex,
	char * error_buf,
	const size_t buf_size
);

/**
 * @brief
 * Maps file into memory and sets `file_start`, `file_end`, `pos`, and `in_fd`
 * members of `RegexMatchWriter`(static function)
 *
 * @param writer Pointer to valid `RegexMatchWriter`
 * @param filepath File to map
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 * @return `1` on success, `0` on failure
 */
static int
RegexMatchWriter_MAPINPUT(
	RegexMatchWriter * writer,
	const char * filepath,
	char * error_buf,
	const size_t buf_size
);

RegexMatchWriter *
RegexMatchWriter_New(
	const char * in_path,
	const char * regex,
	const char * delim,
	int out_fd,
	char * error_buf,
	const size_t buf_size
)
{
	RegexMatchWriter * writer = NULL;

	// Return NULL if filepath or regex are NULL

	if (!in_path)
	{
		NULL_ARG_ERROR(RegexMatchWriter_New, in_path);
		return NULL;
	}

	if (!regex)
	{
		NULL_ARG_ERROR(RegexMatchWriter_New, regex);
		return NULL;
	}

	// Return NULL if file descriptor is invalid

	if (out_fd < 0)
	{
		INVALID_FD(out_fd);
		return NULL;
	}

	// Allocate RegexMatchWriter

	writer = calloc(1, sizeof(RegexMatchWriter));

	if (!writer)
	{
		MEM_ALLOC_ERROR(RegexMatchWriter);
		return NULL;
	}

	// Assign members

	writer->out_fd = out_fd;
	delim = delim ? delim : "\n";
	writer->delim_len = strlen(delim);
	writer->delim = calloc(writer->delim_len + 1, sizeof(char));

	if (!writer->delim)
	{
		free(writer);
		MEM_ALLOC_ERROR(RegexMatchWriter);
		return NULL;
	}
	
	strcpy(writer->delim, delim);

	// Compile regex_t, return NULL on failure

	if (!RegexMatchWriter_REGCOMP(writer, regex, error_buf, buf_size))
	{
		free(writer->delim);
		free(writer);
		return NULL;
	}

	// Map input file to memory, return NULL on failure

	if (!RegexMatchWriter_MAPINPUT(writer, in_path, error_buf, buf_size))
	{
		free(writer->delim);
		regfree(&(writer->pattern));
		free(writer);
		return NULL;
	}

	return writer;
}

int
RegexMatchWriter_WriteNext(
	RegexMatchWriter * writer,
	char * error_buf,
	const size_t buf_size
)
{
	regmatch_t match;
	ssize_t out_bytes;
	int match_len, not_found, tmp_errno;

	// Return -1 if writer is NULL

	if (!writer)
	{
		NULL_ARG_ERROR(RegexMatchWriter_WriteNext, writer);
		return -1;
	}

	// Return 0 if matches already exhausted

	if (writer->pos >= writer->file_end)
		return 0;

	// Search for match, return 0 if not found

	not_found = regexec(&(writer->pattern), writer->pos, 1, &match, 0);

	if (not_found)
		return 0;

	// Write match delimiter if not first match

	if (writer->pos > writer->file_start)
	{
		out_bytes = write(
			writer->out_fd,
			writer->delim,
			writer->delim_len
		);

		tmp_errno = errno;

		if (out_bytes != (ssize_t)writer->delim_len)
		{
			WRITE_ERROR(writer->out_fd, tmp_errno);
			return -1;
		}
	}

	// Advance file cursor to start offset of match

	match_len = match.rm_eo - match.rm_so;
	writer->pos += match.rm_so;

	// Write match to out_fd

	out_bytes = write(writer->out_fd, writer->pos, (size_t)match_len);
	tmp_errno = errno;

	if (out_bytes != (ssize_t)match_len)
	{
		WRITE_ERROR(writer->out_fd, tmp_errno);
		return -1;
	}

	// Advance file cursor to byte after current match

	writer->pos += match_len;
	return match_len;
}

int
RegexMatchWriter_Reset(RegexMatchWriter * writer)
{
	// No-op if NULL

	if (!writer)
		return 0;

	// Set file cursor position to start of file

	writer->pos = writer->file_start;
	return 1;
}

void
RegexMatchWriter_Free(RegexMatchWriter * writer)
{
	// No-op if NULL

	if (!writer)
		return;

	// Destroy memory mapping for search file
 
	munmap(
		writer->file_start,
		(size_t)(writer->file_end - writer->file_start + 1)
	);

	// Close file

	close(writer->in_fd);

	// Free `RegexMatchWriter` resources on the heap

	free(writer->delim);
	regfree(&(writer->pattern));
	free(writer);
}

static int
RegexMatchWriter_REGCOMP(
	RegexMatchWriter * writer,
	const char * regex,
	char * error_buf,
	const size_t buf_size
)
{
	int regcomp_error;

	// Compile regex pattern

	regcomp_error = regcomp(&(writer->pattern), regex, REG_EXTENDED);

	// Check for error

	if (!regcomp_error)
		return 1;

	REGCOMP_ERROR(&(writer->pattern), regcomp_error);
	return 0;
}

static int
RegexMatchWriter_MAPINPUT(
	RegexMatchWriter * writer,
	const char * filepath,
	char * error_buf,
	const size_t buf_size
)
{
	struct stat stat_buf;
	int tmp_errno;
	void * start_addr = NULL;

	// Open file and set `in_fd` member

	if ((writer->in_fd = open(filepath, O_RDONLY)) < 0)
	{
		tmp_errno = errno;
		FILE_OPEN_ERROR(filepath, tmp_errno);
		return 0;
	}

	// Get file size via `fstat`

	if (fstat(writer->in_fd, &stat_buf))
	{
		tmp_errno = errno;
		close(writer->in_fd);
		FILE_STAT_ERROR(filepath, tmp_errno);
		return 0;
	}

	// Use `mmap` to map a region of memory for the file

	start_addr = mmap(
		NULL,
		stat_buf.st_size + 1,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE,
		writer->in_fd,
		0
	);

	tmp_errno = errno;

	if (start_addr == MAP_FAILED)
	{
		close(writer->in_fd);
		FILE_MAP_ERROR(filepath, tmp_errno);
		return 0;
	}

	// Set start/end boundaries of the mapped memory

	writer->file_start = writer->pos = (char *)start_addr;
	writer->file_end = writer->file_start + stat_buf.st_size;

	// Set null terminator at end of memory region

	*(writer->file_end) = '\0';
	return 1;
}
