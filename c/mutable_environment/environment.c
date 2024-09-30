#include <stdio.h>
#include "environment.h"
#include "mystring.h"

extern char **environ;
static environment_t my_environ;

environment_t *init_environment(void)
{
	size_t nvars;

	for (nvars = 0; nvars < MAX_ENV_VARS && environ[nvars]; ++nvars)
		my_environ.vars[nvars] = my_strdup(environ[nvars]);

	my_environ.nvars = nvars;
	my_environ.vars[nvars] = NULL;
	return (&my_environ);
}

void print_environment(void)
{
	size_t i;

	for (i = 0; i < my_environ.nvars; ++i)
		printf("%s\n", my_environ.vars[i]);
}
