CFLAGS := -Wall -Werror -Wextra -pedantic

.PHONY := all clean

all: example

example: *.c
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f example
