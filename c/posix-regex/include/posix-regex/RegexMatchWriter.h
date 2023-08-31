/**
 * @file RegexMatchWriter.h
 *
 * Declaration of opaque type `RegexMatchWriter` and associated
 * function prototypes.
 */

#ifndef ISLANDU_LIVECODES_POSIXREGEX_REGEXMATCHWRITER_H
#define ISLANDU_LIVECODES_POSIXREGEX_REGEXMATCHWRITER_H

#include <stddef.h>

/**
 * Alias for opaque type `struct RegexMatchWriter`
 */
typedef struct RegexMatchWriter RegexMatchWriter;

/**
 * @brief Allocates a new `RegexMatchWriter`
 * @param in_path File to be searched
 * @param regex Regex to match in the file 
 * @param delim Match delimiter in output (default `"\\n"` if `NULL`)
 * @param out_fd Target file descriptor for writing matches
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 * @return Pointer to newly allocated `RegexMatchWriter`
 */
RegexMatchWriter *
RegexMatchWriter_New(
	const char * in_path,
	const char * regex,
	const char * delim,
	int out_fd,
	char * error_buf,
	const size_t buf_size
);

/**
 * @brief Finds next match in the input file and writes it to the output file
 * @param writer Pointer to valid `RegexMatchWriter`
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 * @return Length of matched text (`0` if matches exhausted, `-1` for error)
 */
int
RegexMatchWriter_WriteNext(
	RegexMatchWriter * writer,
	char * error_buf,
	const size_t buf_size
);

/**
 * @brief Resets `RegexMatchWriter` file cursor to start of input file
 * @param writer Pointer to valid `RegexMatchWriter`
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 * @return `1` on success, `0` on failure
 */
int
RegexMatchWriter_Reset(RegexMatchWriter * writer);

/**
 * @brief Frees resources held by `RegexMatchWriter` instance
 * @param writer Pointer to valid `RegexMatchWriter`
 * @param error_buf Buffer for writing error messages (can be `NULL`)
 * @param buf_size Size of `error_buf`
 */
void
RegexMatchWriter_Free(RegexMatchWriter * writer);

#endif // ISLANDU_LIVECODES_POSIXREGEX_REGEXMATCHWRITER_H
