#include <stdio.h>
#include <string.h>
#include "tokenize_cmdline.h"

#define CMDWHITESPACE " \t\n"
#define TOKENVECTOR_ADDARGUMENT(tokvec, s)				\
do {									\
	(tokvec)->tokens[(tokvec)->count] = (s);			\
	(tokvec)->types[(tokvec)->count] = CMDTOKEN_ARG;		\
	++(tokvec)->count;						\
} while (0)

#define TOKENVECTOR_ADDOPERATOR(tokvec, type, strpos)			\
do {									\
	(tokvec)->tokens[(tokvec)->count] = NULL;			\
	(tokvec)->types[(tokvec)->count] = (type);			\
	++(tokvec)->count;						\
	*(strpos)++ = '\0';						\
	if ((type) > CMDTOKEN_SEP) /* operator is 2 characters */	\
		*(strpos)++ = '\0';					\
} while (0)

static void extract_operators(tokenvector_t *tokvec, char *token);

/**
 * tokenize_cmdline - Splits/categorizes tokens in a command line
 * @cmdline: Command line to tokenize (will be modified by function)
 *
 * Return: Pointer to static `tokenvector_t` structure
 */
tokenvector_t *tokenize_cmdline(char *cmdline)
{
	static tokenvector_t tokenvector;
	char *token = NULL;

	/* resetting static token vector */
	tokenvector.count = 0;
	tokenvector.tokens[0] = NULL;
	tokenvector.types[0] = CMDTOKEN_UNKNOWN;

	token = strtok(cmdline, CMDWHITESPACE);

	while (token && tokenvector.count < MAXTOKENS)
	{
		extract_operators(&tokenvector, token);
		token = strtok(NULL, CMDWHITESPACE);
	}

	/* "null terminating" the buffers in the token vector */
	tokenvector.tokens[tokenvector.count] = NULL;
	tokenvector.types[tokenvector.count] = CMDTOKEN_UNKNOWN;

	/* return pointer to the static token vector */
	return (&tokenvector);
}

/**
 * extract_operators - Extracts operators from whitespace-delimited token
 * @tokvec: Pointer to `tokenvector_t` structure
 * @token: Pointer to whitespace-separated string
 */
static void extract_operators(tokenvector_t *tokvec, char *token)
{
	char *leader = NULL, *follower = NULL;
	cmdtokentype_t type;

	leader = follower = token;

	while (*leader)
	{
		switch (*leader)
		{
		case '>':
			type = *(leader + 1) == '>'
				? CMDTOKEN_APPEND_OUT
				: CMDTOKEN_REDIR_OUT;
			break;
		case '<':
			type = *(leader + 1) == '<'
				? CMDTOKEN_HEREDOC
				: CMDTOKEN_REDIR_IN;
			break;
		case '|':
			type = *(leader + 1) == '|'
				? CMDTOKEN_OR
				: CMDTOKEN_PIPE;
			break;
		case '&':
			type = CMDTOKEN_AND;
			break;
		case ';':
			type = CMDTOKEN_SEP;
			break;
		default:
			++leader;
			continue;
		}

		if (leader > follower)
			TOKENVECTOR_ADDARGUMENT(tokvec, follower);

		TOKENVECTOR_ADDOPERATOR(tokvec, type, leader);
		follower = leader;
	}

	if (leader > follower)
		TOKENVECTOR_ADDARGUMENT(tokvec, follower);
}
