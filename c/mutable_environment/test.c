#include <stdio.h>
#include <stdlib.h>
#include "environment.h"

int main(void)
{
	environment_t *env_ptr = NULL;

	env_ptr = init_environment();

	if (!env_ptr)
	{
		fprintf(stderr, "Could not initialize environment variable manager\n");
		exit(EXIT_FAILURE);
	}

	print_environment();
	return (0);
}
