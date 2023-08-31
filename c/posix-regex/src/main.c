/**
 * @file main.c
 *
 * Demo driver file using `RegexMatchWriter` struct and
 * associated functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "posix-regex/RegexMatchWriter.h"

/** Size of error buffer */
#define BUF_SIZE 1024UL

/** Regex for matching email addresses */
#define EMAIL_RE "\\b[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\\b"

/** Path to test search file */
#define TEST_FILE "./test-data/emails.txt"

/**
 * @brief Driver-code entry point
 *
 * @return `EXIT_SUCCESS` | `EXIT_FAILURE`
 */
int
main(void)
{
	RegexMatchWriter * writer = NULL;
	int match_count, write_result;
	char error_buf[BUF_SIZE] = { '\0' };

	// Allocate RegexMatchWriter for extracting email addresses from file

	writer = RegexMatchWriter_New(
		TEST_FILE,
		EMAIL_RE,
		"\n",
		STDOUT_FILENO,
		error_buf,
		BUF_SIZE
	);

	if (!writer)
	{
		fputs(error_buf, stderr);
		exit(EXIT_FAILURE);
	}

	// Write/count matches until exhausted or error occurs

	match_count = -1;

	do
	{
		++match_count;

		write_result = RegexMatchWriter_WriteNext(
			writer,
			error_buf,
			BUF_SIZE
		);

	} while (write_result > 0);

	// Free RegexMatchWriter resources

	RegexMatchWriter_Free(writer);

	if (write_result < 0)
	{
		fputs(error_buf, stderr);
		exit(EXIT_FAILURE);
	}

	// Print match count

	printf("\nMatch count: %d\n", match_count);
	return EXIT_SUCCESS;
}
