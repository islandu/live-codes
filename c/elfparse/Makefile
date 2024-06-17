CFLAGS := -g3 -Wall -Werror -Wextra -pedantic
CSTD := gnu89

.PHONY := all clean

all: test

test: *.c *.h
	@gcc -o $@ $^ $(CFLAGS) -std=$(CSTD)

clean:
	@rm -f test
