#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "c_to_cpp/person.h"

int person_init(person_t *person, const char *name, unsigned int age)
{
	if (!person || !name)
		return -1;

	person->name[sizeof(person->name) - 1] = '\0';
	strncpy(person->name, name, sizeof(person->name) - 1);
	person->age = age;
	return 0;
}

int person_to_string(const person_t *person, char *buf, size_t n)
{
	int len;

	if (!person || !buf)
		return -1;

	len = snprintf(buf, n,
		       "Person { name: '%s', age: %u }",
		       person->name, person->age);

	return len;
}

int person_birthday(person_t *person)
{
	if (!person || person->age == UINT_MAX)
		return -1;

	++person->age;
	return 0;
}
