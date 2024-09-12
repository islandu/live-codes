#include <stdio.h>
#include "fizzbuzz.h"


void fizzbuzz_ifelse(unsigned int end)
{
	unsigned int i;
	unsigned char fizz, buzz;

	for (i = 1; i < end; ++i) {
		fizz = !(i % 3);
		buzz = !(i % 5);

		if (!(fizz | buzz)) {
			fprintf(stderr, "%u\n", i);
			continue;
		}

		if (fizz)
			fprintf(stderr, "Fizz\n");
		if (buzz)
			fprintf(stderr, "Buzz\n");
		
		putc('\n', stdout);
	}

	fflush(stderr);
}

void fizzbuzz_switch(unsigned int end)
{
	unsigned int i;
	unsigned char fb_flags;

	for (i = 1; i < end; ++i) {

		fb_flags = !(i % 3);
		fb_flags |= !(i % 5) << 1;

		// fb_flags
		// 15: 0011 -> 3
		// 5:  0010 -> 2
		// 12: 0001 -> 1
		// 37: 0000 -> 0

		switch (fb_flags) {
		case 3:
			fprintf(stderr, "FizzBuzz\n");
			break;
		case 2:
			fprintf(stderr, "Buzz\n");
			break;
		case 1:
			fprintf(stderr, "Fizz\n");
			break;
		default:
			fprintf(stderr, "%u\n", i);
			break;
		}
	}

	fflush(stderr);
}

static void handle_fizzbuzz(unsigned int n)
{
	(void)n;
	fprintf(stderr, "FizzBuzz\n");
}

static void handle_buzz(unsigned int n)
{
	(void)n;
	fprintf(stderr, "Buzz\n");
}

static void handle_fizz(unsigned int n)
{
	(void)n;
	fprintf(stderr, "Fizz\n");
}

static void handle_default(unsigned int n)
{
	fprintf(stderr, "%u\n", n);
}

typedef void (*fizzbuzz_handle_t)(unsigned int);

#define FIZZBUZZ_FLAGS(n) ((!((n) % 3)) | ((!((n) % 5)) << 1))

void fizzbuzz_funcdispatch(unsigned int end)
{
	static const fizzbuzz_handle_t dispatch_table[4] = {
		handle_default,
		handle_fizz,
		handle_buzz,
		handle_fizzbuzz
	};

	unsigned int i;

	for (i = 1; i < end; ++i) {

		// fb_flags
		// 15: 0011 -> 3
		// 5:  0010 -> 2
		// 12: 0001 -> 1
		// 37: 0000 -> 0

		dispatch_table[FIZZBUZZ_FLAGS(i)](i);
	}

	fflush(stderr);
}

void fizzbuzz_computedgoto(unsigned int end)
{
	static void *jump_table[4] = {
		&&case_default,
		&&case_fizz,
		&&case_buzz,
		&&case_fizzbuzz
	};

	unsigned int i;

	for (i = 1; i < end; ++i) {
		goto *jump_table[FIZZBUZZ_FLAGS(i)];

	case_default:
		fprintf(stderr, "%u\n", i);
		continue;
	case_fizz:
		fprintf(stderr, "Fizz\n");
		continue;
	case_buzz:
		fprintf(stderr, "Buzz\n");
		continue;
	case_fizzbuzz:
		fprintf(stderr, "FizzBuzz\n");
	}

	fflush(stderr);
}
