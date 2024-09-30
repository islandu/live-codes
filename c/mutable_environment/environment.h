#ifndef ATLAS_SHELLV2_ENVIRONMENT_H
#define ATLAS_SHELLV2_ENVIRONMENT_H

#include <stddef.h>

#define MAX_ENV_VARS 4096ul

typedef struct environment
{
	size_t nvars;
	char *vars[MAX_ENV_VARS + 1];
} environment_t;

environment_t *init_environment(void);
void print_environment(void);

#endif /* !ATLAS_SHELLV2_ENVIRONMENT_H */
