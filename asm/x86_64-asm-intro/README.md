# `asm/x86_64-asm-intro`

Starting from a "sane" implementation of `strlen` in C...

```c
#include <stddef.h>

size_t my_strlen(const char *str)
{
	size_t counter;

	for (counter = 0; str[counter]; ++counter)
		;

	return (counter);
}
```

`for`, `while`, and `do`/`while` loops are all high-level features of C. In assembly we don't have loop constructs, but we can take one intermediary step before writing this in assembly. Below is an implementation of `strlen` that only uses `goto` and code labels to simulate a loop (which is much closer to the conditional/unconditional jumps we will have to use in assembly).


```c
#include <stddef.h>

/**
 * my_strlen - Hand-rolled `strlen` in C, but with an ASM fashion sense!
 * @str: Pointer to first character of null-terminated string
 *
 * Return: Length of the string (not counting null terminator)
 */
size_t my_strlen(const char *str)
{
    size_t rcx;     /* stack variable named `rcx`, but in assembly
                       just use the `rcx` ('counter') register */

    rcx ^= rcx;     /* `xor rcx, rcx`, zero-out the register */

loop:
    if (!str[rcx])  /* `cmp byte[rdi+rcx], 0`, check for '\0' */
        goto done;  /* `jz .done` */
    ++rcx;          /* `inc rcx` */
    goto loop;      /* `jmp .loop` */
done:
    return (rcx);   /* `mov rax rcx`, set return register `rax` */
}
```

So here's a NASM-assembler friendly implementation of `strlen`...

```
my_strlen:  ; Label for the function
    ; Setting up the stack frame (always do this!)
    push    rbp                 ; Preserve base pointer on the stack
    mov     rbp, rsp            ; Set the base pointer to the current stack pointer

    ; Begin my_strlen function logic (see corresponding C code)
    xor     rcx, rcx            ; Zero-out rcx (the 'counter' register)

.loop:  ; Label for start of the count loop
    cmp     byte[rdi+rcx], 0    ; Check if current character is a null-terminator
    jz      .done               ; Jump to .done if null-terminator reached
    inc     rcx                 ; Increment rax (character counter)
    jmp     .loop               ; Jump back to the start of the loop

.done:  ; Label for breaking out of the loop
    mov     rax, rcx            ; Assign 'counter' value to rax (return register)

    ; Tearing down the stack frame (always do this!)
    mov     rsp, rbp            ; Restore previous stack pointer
    pop     rbp                 ; Restore previous base pointer
    ret                         ; Return from the function
```

If you want to build/test the example code, just run the following from this directory...
```bash
$ make
$ ./strlen_c 'qwerty'  # run the c version
6
$ ./strlen_asm 'hello' # run the assembly version
5
```

Feel free to use this example as a starting point when implementing your assigned `<string.h>` functions with NASM assembler (see `Makefile` or the project for example invocation). Good luck!
