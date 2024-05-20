#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "directory_reader.h"

#define SHOULD_PRINT(entry, flag_all) \
	((entry)->d_name[0] != '.' || (flag_all))

/* 
static int print_direntry_name(directory_reader_t *parser)
{
	if (!SHOULD_PRINT(parser->current_entry, parser->flag_all))
		return (0);

	printf("%s ", parser->current_entry->d_name);
	return (0);
}
 */

static int print_longlistfmt(directory_reader_t *parser)
{
	struct stat statbuf;
	longlistfmt_t longlist;
	const char *entry_name = NULL;
	const char *entry_path = NULL;

	if (!SHOULD_PRINT(parser->current_entry, parser->flag_all))
		return (0);
	
	entry_name = parser->current_entry->d_name;
	entry_path = path_join(parser->path, entry_name);

	if (lstat(entry_path, &statbuf) == -1)
		return (-1);

	longlistfmt_init(&longlist, entry_name, &statbuf);
	longlistfmt_print(&longlist);
	return (0);
}

/**
 * main - Entry point for directory-parser demo
 * @arg: Number of CL args
 * @argv: Argument vector
 * 
 * Return: `EXIT_SUCCESS` or `EXIT_FAILURE`
 */
int main(int argc, char **argv)
{
	directory_reader_t parser;
	const char *directory_path = NULL;

	/* Expecting a single directory-path argument */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s DIRPATH\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	directory_path = argv[1];

	/* Opening directory and initializing parser */
	if (directory_reader_init(&parser, directory_path, 1) == -1)
	{
		fprintf(stderr,
			"Failure opening directory '%s'\n",
			directory_path);
		return (EXIT_FAILURE);
	}

	/* Traversing the directory's entries and invoking the item_handler */
	/* TODO: make an item_handler */
	if (directory_reader_foreach(&parser, print_longlistfmt) == -1)
	{
		fprintf(stderr,
			"Error occurred parsing directory '%s'\n",
			directory_path);
		return (EXIT_FAILURE);
	}

	/* Cleanup, closing the directory */
	directory_reader_destroy(&parser);
	return (EXIT_SUCCESS);
}
