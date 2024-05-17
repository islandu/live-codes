#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "directory_reader.h"

#define SHOULD_PRINT(entry, flag_all) \
	((entry)->d_name[0] != '.' || (flag_all))

char PATH_BUF[4096];

static int print_direntry_name(directory_reader_t *parser)
{
	if (!SHOULD_PRINT(parser->current_entry, parser->flag_all))
		return (0);

	printf("%s ", parser->current_entry->d_name);
	return (0);
}

/**
 * main - Entry point for directory-parser demo
 * @arg - Number of CL args
 * @argv - Argument vector
 * 
 * Return: `EXIT_SUCCESS` or `EXIT_FAILURE`
 */
int main(int argc, char **argv)
{
	directory_reader_t parser;
	const char *directory_path = NULL;
	int flag_all = 1;

	/* Expecting a single directory-path argument */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s DIRPATH\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	directory_path = argv[1];

	/* Opening directory and initializing parser */
	if (directory_reader_init(&parser, directory_path) == -1)
	{
		fprintf(stderr,
			"Failure opening directory '%s'\n",
			directory_path);
		return (EXIT_FAILURE);
	}

	parser.flag_all = flag_all;

	/* Traversing the directory's entries and invoking the item_handler */
	/* TODO: make an item_handler */
	if (directory_reader_foreach(&parser, print_direntry_name) == -1)
	{
		fprintf(stderr,
			"Error occurred parsing directory '%s'\n",
			directory_path);
		return (EXIT_FAILURE);
	}

	putc('\n', stdout);

	/* Cleanup, closing the directory */
	directory_reader_destroy(&parser);
	return (EXIT_SUCCESS);
}
