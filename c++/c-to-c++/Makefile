CC := gcc
CPP_CC := g++
CFLAGS := -Wall -Werror -Wextra -pedantic
CSTD := gnu89
CPPSTD := c++17
INCLUDE := -Iinclude

C_SRC := $(wildcard src/*.c)
CPP_SRC := $(wildcard src/*.cpp)

.PHONY := c cpp clean

cpp: build/cpp_test

c: build/c_test

build/cpp_test: $(CPP_SRC) | build
	@$(CPP_CC) $(CFLAGS) $(INCLUDE) -std=$(CPPSTD) -o $@ $^

build/c_test: $(C_SRC) | build
	@$(CC) $(CFLAGS) $(INCLUDE) -std=$(CSTD) -o $@ $^ 

build:
	@mkdir -p build

clean:
	@rm -rf build
