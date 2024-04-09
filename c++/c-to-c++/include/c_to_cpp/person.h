#ifndef _CTOCPP_PERSON_H
#define _CTOCPP_PERSON_H

#include <stddef.h>

typedef struct person {
	char name[64];
	unsigned int age;
} person_t;

int person_init(person_t *person, const char *name, unsigned int age);

int person_to_string(const person_t *person, char *buf, size_t n);

int person_birthday(person_t *person);

#endif /* _CTOCPP_PERSON_H */
