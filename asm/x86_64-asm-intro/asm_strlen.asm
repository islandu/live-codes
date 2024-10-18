BITS 64 ; Indicates 64-bit architecture

section .data
    ; No global variables used so this can be blank

section .text
    global my_strlen    ; Make the function globally accessible

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
