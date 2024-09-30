#include <stdlib.h>
#include "mystring.h"

size_t my_strlen(const char *s)
{
	size_t len = 0;

	while (*s++)
		++len;

	return (len);
}

char *my_strdup(const char *s)
{
	size_t len, i;
	char *copy = NULL;

	len = my_strlen(s);
	copy = malloc(len + 1);

	if (!copy)
		return NULL;

	for (i = 0; i < len; ++i)
		copy[i] = s[i];

	copy[len] = '\0';
	return (copy);
}

