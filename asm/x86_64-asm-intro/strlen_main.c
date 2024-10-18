#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define USAGE_FMT "USAGE: %s STRING\n"

size_t my_strlen(const char *str);

int main(int argc, char **argv)
{
	size_t len;

	if (argc != 2)
	{
		fprintf(stderr, USAGE_FMT, argv[0]);
		exit(EXIT_FAILURE);
	}

	len = my_strlen(argv[1]);
	printf("%lu\n", len);
	return (0);
}
