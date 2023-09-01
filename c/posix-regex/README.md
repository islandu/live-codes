# `c/posix-regex`

## Abstract
Demonstrates regex pattern matching using the POSIX C library--a core component of most Unix-derived systems (e.g., Linux distros, macOS, AIX, etc.).

## Topics
In the code you will find examples of the following:
- How to use the types/functions in the `<regex.h>` header (not part of the C standard library, but included on all POSIX systems)
- How to iteratively find all the email addresses in a text file
- How to map a file to virtual memory with `mmap` (so you can treat file contents as a string without copying all the data to RAM at once). This is necessary because the POSIX `regexec` library call accepts the search space as a null-terminated string.

_Note: If you require Perl-compatible regexes in your C project and/or your code needs to support Windows, you should take a look at [PCRE2](https://github.com/PCRE2Project/pcre2)._

## Code
```
c/posix-regex
├── include
│   └── posix-regex
│       └── RegexMatchWriter.h
├── Makefile
├── README.md
├── src
│   ├── include
│   │   └── posix-regex
│   │       └── macros.h
│   ├── main.c
│   └── RegexMatchWriter.c
└── test-data
    └── emails.txt
```
