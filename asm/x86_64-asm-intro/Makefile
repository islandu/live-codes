CFLAGS := -Wall -Werror -Wextra -pedantic -std=gnu89

.PHONY := all clean

all: strlen_asm strlen_c

clean:
	rm -f *.o strlen_asm strlen_c

strlen_asm: strlen_main.o asm_strlen.o
	gcc -o $@ $(CFLAGS) $^

strlen_c: strlen_main.o c_strlen.o
	gcc -o $@ $(CFLAGS) $^

asm_strlen.o: asm_strlen.asm
	nasm -f elf64 $^

c_strlen.o: c_strlen.c
	gcc -c -o $@ $(CFLAGS) $^

strlen_main.o: strlen_main.c
	gcc -c -o $@ $(CFLAGS) $^
