#include <stdlib.h>
#include <string.h>
#include "directory_reader.h"

int directory_reader_init(directory_reader_t *parser, const char *path)
{
	DIR *dir = NULL;

	if (!parser || !path)
		return (-1);

	dir = opendir(path);

	if (!dir)
		return (-1);

	parser->directory = dir;
	parser->path = path;
	parser->current_entry = NULL;
	parser->stop = 0;

	return (0);
}

struct dirent *directory_reader_next(directory_reader_t *parser)
{
	struct dirent *next_entry = NULL;

	if (parser->stop)
		return (NULL);

	next_entry = readdir(parser->directory);

	if (next_entry)
	{
		parser->current_entry = next_entry;
	}
	else
	{
		parser->stop = 1;
		parser->current_entry = NULL;
	}

	return (next_entry);
}

int directory_reader_foreach(directory_reader_t *parser, dirent_handler_t item_handler)
{
	int entry_count = 0;

	if (!parser || !item_handler)
		return (-1);

	while (directory_reader_next(parser))
	{
		if (item_handler(parser) == -1)
		{
			/* print an error message for this entry but continue */
			;
		}

		++entry_count;
	}

	return (entry_count);
}

void directory_reader_destroy(directory_reader_t *parser)
{
	if (!parser)
		return;

	closedir(parser->directory);
	memset(parser, 0, sizeof(*parser));
}

