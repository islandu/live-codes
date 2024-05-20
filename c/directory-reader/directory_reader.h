#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * struct directory_reader - Iterator for parsing `DIR` stream
 * @directory: Pointer to `DIR` instance
 * @path: Path to directory in file system
 * @current_entry: Pointer to current `struct dirent`
 * @stop: Flag to indicate that directory entries have been exhausted
 * @flag_all: `1` if '-a' option passed, else `0`
 */
typedef struct directory_reader {
	DIR *directory;
	const char *path;
	struct dirent *current_entry;
	int stop;
	int flag_all;
} directory_reader_t;

typedef int (*dirent_handler_t)(directory_reader_t *parser);

/* directory_reader.c */

int directory_reader_init(directory_reader_t *parser, const char *path, int flag_all);

struct dirent *directory_reader_next(directory_reader_t *parser);

int directory_reader_foreach(directory_reader_t *parser, dirent_handler_t item_handler);

void directory_reader_destroy(directory_reader_t *parser);

/* helpers.c */

typedef struct longlistfmt {
	char mode[16];
	nlink_t nlinks;
	const char *user;
	const char *group;
	off_t size;
	const char *modified;
	const char *entry_name;
} longlistfmt_t;

const char *dirent_type_name(unsigned char d_type);
const char *path_join(const char *dirpath, const char *entry_name);
int mode_to_str(char *buf, mode_t mode);

int longlistfmt_init(longlistfmt_t *longlist,
		     const char *entry_name,
		     struct stat *statbuf);

void longlistfmt_print(longlistfmt_t *longlist);

#endif /* DIRECTORYREADER_H */
