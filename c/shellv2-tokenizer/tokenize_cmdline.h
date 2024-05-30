#ifndef LIVECODES_SHELLV2TOKENIZER_TOKENIZECMDLINE_H
#define LIVECODES_SHELLV2TOKENIZER_TOKENIZECMDLINE_H

#include <stddef.h>

#define MAXTOKENS 64

/**
 * enum cmdtokentype - Type of command token
 * @CMDTOKEN_UNKNOWN: Unknown type
 * @CMDTOKEN_ARG: Arg or command
 * @CMDTOKEN_REDIR_OUT: > operator
 * @CMDTOKEN_REDIR_IN: < operator
 * @CMDTOKEN_PIPE: | operator
 * @CMDTOKEN_SEP: ; operator
 * @CMDTOKEN_APPEND_OUT: >> operator
 * @CMDTOKEN_HEREDOC: << operator
 * @CMDTOKEN_AND: && operator
 * @CMDTOKEN_OR: || operator
 */
typedef enum cmdtokentype
{
	CMDTOKEN_UNKNOWN,
	CMDTOKEN_ARG,
	CMDTOKEN_REDIR_OUT,
	CMDTOKEN_REDIR_IN,
	CMDTOKEN_PIPE,
	CMDTOKEN_SEP,
	/* 2 characters */
	CMDTOKEN_APPEND_OUT,
	CMDTOKEN_HEREDOC,
	CMDTOKEN_AND,
	CMDTOKEN_OR
} cmdtokentype_t;

/**
 * struct tokenvector - Buffer for tokenizing command line
 * @count: Number of tokens parsed from command line
 * @tokens: Array of pointers to token locations in the command line
 * @types: Array of `tokentype_t` values (parallel with `tokens`)
 */
typedef struct tokenvector
{
	size_t count;
	char *tokens[MAXTOKENS + 1];
	cmdtokentype_t types[MAXTOKENS + 1];
} tokenvector_t;

/**
 * tokenize_cmdline - Splits/categorizes tokens in a command line
 * @cmdline: Command line to tokenize (will be modified by function)
 *
 * Return: Pointer to static `tokenvector_t` structure
 */
tokenvector_t *tokenize_cmdline(char *cmdline);

#endif /* LIVECODES_SHELLV2TOKENIZER_TOKENIZECMDLINE_H */
