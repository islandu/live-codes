CFLAGS := -Wall -Werror -Wextra -pedantic
CSTD := gnu89

.PHONY := all clean

all: tokenize_test

tokenize_test: *.c *.h
	@gcc -o $@ *.c $(CFLAGS) -std=$(CSTD)

clean:
	@rm -f tokenize_test
