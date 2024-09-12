CFLAGS := -Wall -Werror -Wextra

.PHONY := all build clean

all: build/benchmarks

run-benchmarks: build/benchmarks
	@./build/benchmarks 2> /dev/null

build/benchmarks: build/benchmarks.o build/fizzbuzz.o
	g++ -o $@ $^ -lbenchmark -lpthread $(CFLAGS)

build/benchmarks.o: benchmarks.cpp build
	g++ -c -o $@ $^ $(CFLAGS)

build/fizzbuzz.o: fizzbuzz.c build
	gcc -c -o $@ $^ $(CFLAGS)

build:
	@mkdir -p build

clean:
	@rm -rf build
