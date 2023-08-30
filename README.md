# live-codes
Source code from live programming demos at Holberton School Tulsa. The code in this repository is provided for reference purposes (post-demo) and the projects may not be particularly useful as standalone tutorials.

## C
### `c/posix-regex`
Demonstrates regex pattern matching using the POSIX C library--a core compponent of most Unix-derived systems (e.g., Linux distros, macOS, AIX, etc.).
- How to use the types/functions in the `<regex.h>` header (not part of the C standard library, but included on all POSIX systems)
- How to iteratively find all the email addresses in a text file
- How to map a file to virtual memory with `mmap` (so you can treat file contents as a string without copying all the data to RAM at once)

_Note: If you require Perl-compatible regexes in your C project and/or your code needs to support Windows, you should take a look at [PCRE2](https://github.com/PCRE2Project/pcre2)._

## C++
### `c++/template-metaprogramming`
Demonstrates the use of template metaprogramming (C++17) to create generic, OOP-friendly interfaces.
- How to use the strategy pattern (non-template example)
- How to use C++ class templates to abstract the context/strategy base classes such that they can be specialized for any purpose
- How to use compile-time assertions to ensure concrete implementations of context/strategy class templates are compatible with one another

## Python
### `python/flask-rest-api`
Demonstrates the use of the `flask` python package to quickly create a simple REST API.
- How to define and implement `GET`/`POST`/etc. HTTP methods for a path within the application's base address
- How to accept query parameters and JSON request bodies
- How to set status codes and send a JSON response body back to the client
- How to implement the basic-auth scheme and best practices for storing client passwords
