# `c++/template-metaprogramming`

## Abstract
Demonstrates the use of template metaprogramming (C++17) to create generic, OOP-friendly interfaces.

## Topics
In the code you will find examples of the following:
- How to use the strategy pattern (non-template example)
- How to use C++ class templates to abstract the context/strategy base classes such that they can be specialized for any purpose
- How to use compile-time assertions to ensure concrete implementations of context/strategy class templates are compatible with one another

## Code
```
c++/template-metaprogramming/
├── include
│   └── metalivecode
│       ├── nontemplates
│       │   ├── MathContext.h
│       │   ├── MathStrategy.h
│       │   ├── Multiply.h
│       │   └── Power.h
│       └── templates
│           ├── ContextTemplate.hpp
│           ├── print_vector.hpp
│           ├── SkipStrategy.hpp
│           ├── SortStrategy.hpp
│           ├── StrategyTemplate.hpp
│           ├── TakeStrategy.hpp
│           ├── VectorContext.hpp
│           └── VectorStrategy.hpp
├── Makefile
├── README.md
└── src
    ├── main.cpp
    ├── MathContext.cpp
    ├── MathStrategy.cpp
    ├── Multiply.cpp
    └── Power.cpp
```
