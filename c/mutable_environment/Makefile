.PHONY := all clean

all: test

test: *.c *.h
	gcc -o $@ $^ -Wall -Werror -Wextra -pedantic

clean:
	rm -f test
