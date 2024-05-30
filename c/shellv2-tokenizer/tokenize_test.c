#include <stdio.h>
#include <unistd.h>
#include "tokenize_cmdline.h"

static const char *TOKENTYPEMAP[10] = {
	"Unknown token type",
	"command argument",
	"> operator",
	"< operator",
	"| operator",
	"; operator",
	">> operator",
	"<< operator",
	"&& operator",
	"|| operator"
};

int main(int argc, char **argv)
{
	char cmdline[] = "ls  -la| grep <pattern.txt\n";
	tokenvector_t *tokvec = NULL;
	size_t i;

	(void)argc;
	(void)argv;

	printf("Tokenizing command line: '%s'\n", cmdline);

	tokvec = tokenize_cmdline(cmdline);
	if (!tokvec)
	{
		fputs("Failed to tokenize command line\n", stderr);
		return (1);
	}

	for (i = 0; i < tokvec->count; ++i)
	{
		if (tokvec->tokens[i])
			printf("Token %02lu: '%s'\n",
			       i + 1,
			       tokvec->tokens[i]);
		else
			printf("Token %02lu: (%s)\n",
			       i + 1,
			       TOKENTYPEMAP[tokvec->types[i]]);
	}

	/* 'ls' token is here */
	/* char **cmd1_args = &tokvec->tokens[0]; */

	/* 'grep' token is here */
	/* char **cmd2_args = &tokvec->tokens[3]; */

	/* gotta find the command absolute paths */
	/* const char *cmd1_path = NULL;
	const char *cmd2_path = NULL;
	char **envp = NULL; */

	/* execve(cmd1_path, cmd1_args, envp);
	execve(cmd2_path, cmd2_args, envp); */

	return (0);
}