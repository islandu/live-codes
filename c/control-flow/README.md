# Control Flow Techniques in C

This repo shows 3 additional control-flow techniques beypnd conditional `if`/`else` in C programming. I have implemented 4 versions of FizzBuzz, the first of which uses conditional jumps and is benchmarked against the other 3 implementations.

## Functions
- fizzbuzz_ifelse
- fizzbuzz_switch
- fizzbuzz_funcdispatch
- fizzbuzz_computedgoto

By using `switch` statements, function dispatching, or computed `goto` (i.e., a computed jump rather than a conditional one) where possible, the size of your binaries will be significantly smaller and you will notice performance gains as well.

## Benchmarks

I used Google's C++ benchmark library to benchmark the performance of these 4 implementations of FizzBuzz. If you benchmark locally, you should see performance proportions similar to the following.

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
BM_fizzbuzz_ifelse         14424124 ns     14411778 ns           48
BM_fizzbuzz_switch          3139468 ns      3137835 ns          215
BM_fizzbuzz_funcdispatch    3223698 ns      3222345 ns          219
BM_fizzbuzz_computedgoto    3203706 ns      3201949 ns          216
```

- The `switch` implementation is 4.59x faster than the conditional-jump implementation.
- The function-dispatching implementation is 4.47x faster than the conditional-jump implementation.
- The computed-goto implementation is 4.5x faster than the conditional-jump implementation.
