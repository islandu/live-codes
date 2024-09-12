#include <benchmark/benchmark.h>
#include "fizzbuzz.h"

static void BM_fizzbuzz_ifelse(benchmark::State& state)
{
    for (auto _ : state) {
        fizzbuzz_ifelse(16);    // 1-15
        fizzbuzz_ifelse(61);    // 1-60
        fizzbuzz_ifelse(241);   // 1-240
        fizzbuzz_ifelse(961);   // 1-960
        fizzbuzz_ifelse(3841);  // 1-3840
        fizzbuzz_ifelse(15361); // 1-15360
    }
}

static void BM_fizzbuzz_switch(benchmark::State& state)
{
    for (auto _ : state) {
        fizzbuzz_switch(16);    // 1-15
        fizzbuzz_switch(61);    // 1-60
        fizzbuzz_switch(241);   // 1-240
        fizzbuzz_switch(961);   // 1-960
        fizzbuzz_switch(3841);  // 1-3840
        fizzbuzz_switch(15361); // 1-15360
    }
}

static void BM_fizzbuzz_funcdispatch(benchmark::State& state)
{
    for (auto _ : state) {
        fizzbuzz_funcdispatch(16);    // 1-15
        fizzbuzz_funcdispatch(61);    // 1-60
        fizzbuzz_funcdispatch(241);   // 1-240
        fizzbuzz_funcdispatch(961);   // 1-960
        fizzbuzz_funcdispatch(3841);  // 1-3840
        fizzbuzz_funcdispatch(15361); // 1-15360
    }
}

static void BM_fizzbuzz_computedgoto(benchmark::State& state)
{
    for (auto _ : state) {
        fizzbuzz_computedgoto(16);    // 1-15
        fizzbuzz_computedgoto(61);    // 1-60
        fizzbuzz_computedgoto(241);   // 1-240
        fizzbuzz_computedgoto(961);   // 1-960
        fizzbuzz_computedgoto(3841);  // 1-3840
        fizzbuzz_computedgoto(15361); // 1-15360
    }
}

BENCHMARK(BM_fizzbuzz_ifelse);
BENCHMARK(BM_fizzbuzz_switch);
BENCHMARK(BM_fizzbuzz_funcdispatch);
BENCHMARK(BM_fizzbuzz_computedgoto);

BENCHMARK_MAIN();
