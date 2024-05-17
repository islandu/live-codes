#ifndef DIRECTORYREADER_H
#define DIRECTORYREADER_H

#include <dirent.h>

/**
 * struct directory_reader - Iterator for parsing `DIR` stream
 * @directory: Pointer to `DIR` instance
 * @path: Path to directory in file system
 * @current_entry: Pointer to current `struct dirent`
 * @stop: Flag to indicate that directory entries have been exhausted
 * @flag_all: 1 if `-a` option passed, else `0`
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

int directory_reader_init(directory_reader_t *parser, const char *path);

struct dirent *directory_reader_next(directory_reader_t *parser);

int directory_reader_foreach(directory_reader_t *parser, dirent_handler_t item_handler);

void directory_reader_destroy(directory_reader_t *parser);

/* helpers.c */

const char *dirent_type_name(unsigned char d_type);
const char *path_join(const char *dirpath, const char *entry_name);

#endif /* DIRECTORYREADER_H */
