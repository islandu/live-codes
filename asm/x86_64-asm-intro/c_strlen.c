#include <stddef.h>

/*

Sane C implementation of `strlen` using a loop

size_t my_strlen(const char *str)
{
	size_t counter;

	for (counter = 0; str[counter]; ++counter)
		;

	return (counter);
}

...but we don't have `for`, `while`, or `do`/`while` in ASM.
The C function below uses `goto` to create a loop similar to ASM
*/

/**
 * my_strlen - Hand-rolled `strlen` in C, but with an ASM fashion sense!
 * @str: Pointer to first character of null-terminated string
 *
 * Return: Length of the string (not counting null terminator)
 */
size_t my_strlen(const char *str)
{
	size_t rcx;		/* stack variable named `rcx`, but in assembly
				   just use the `rcx` ('counter') register */

	rcx ^= rcx;		/* `xor rcx, rcx`, zero-out the register */

loop:
	if (!str[rcx])		/* `cmp byte[rdi+rcx], 0`, check for '\0' */
		goto done;	/* `jz .done` */
	++rcx;			/* `inc rcx` */
	goto loop;		/* `jmp .loop` */
done:
	return (rcx); 		/* `mov rax rcx`, set return register `rax` */
}
