#include <stdio.h>
#include "c_to_cpp/person.h"

int main(void)
{
	person_t person;
	char buf[256] = {'\0'};

	person_init(&person, "Sam Sepiol", 28);
	person_to_string(&person, buf, sizeof(buf) - 1);
	puts(buf);
	person_birthday(&person);
	person_to_string(&person, buf, sizeof(buf) - 1);
	puts(buf);

	return 0;
}
