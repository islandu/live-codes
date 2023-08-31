/**
 * @file macros.h
 *
 * Macro functions and constants
 */

#ifndef ISLANDU_LIVECODES_POSIXREGEX_MACROS_H
#define ISLANDU_LIVECODES_POSIXREGEX_MACROS_H

#include <regex.h>
#include <stdio.h>
#include <string.h>

/** Format string for `NULL_ARG_ERROR` */
#define NULL_ARG_FMT "%s argument '%s' cannot be NULL"

/** Format string for `MEM_ALLOC_ERROR` */
#define MEM_ALLOC_FMT "%s allocation failed"

/** Format string for `INVALID_FD` */
#define INVALID_FD_FMT "Invalid file descriptor (%d)"

/** Format string for `REGCOMP_ERROR` */
#define REGCOMP_FMT "Failed to compile regex '%s': "

/** Format string for `FILE_OPEN_ERROR` */
#define FILE_OPEN_FMT "Failed to open file '%s' for reading (%s)"

/** Format string for `FILE_STAT_ERROR` */
#define FILE_STAT_FMT "Failed to get status of file '%s' (%s)"

/** Format string for `FILE_MAP_ERROR` */
#define FILE_MAP_FMT "Failed to map file '%s' into virtual memory (%s)"

/** Format string for `WRITE_ERROR` */
#define WRITE_FMT "Error writing to file descriptor %d (%s)"

/** Converts token to string literal */
#define TOKEN_STR(t) #t

/** Converts actual buffer size to safely writable size */
#define SAFE_SIZE(n) ((n) > 0 ? (n) - 1 : 0)

/** Writes formatted null-argument message to `error_buf` */
#define NULL_ARG_ERROR(fn, arg)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		NULL_ARG_FMT,		\
		TOKEN_STR(fn),		\
		TOKEN_STR(arg)		\
	)

/** Writes formatted allocation-failure message to `error_buf` */
#define MEM_ALLOC_ERROR(t)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		MEM_ALLOC_FMT,		\
		TOKEN_STR(t)		\
	)

/** Writes formatted invalid file-descriptor message to `error_buf` */
#define INVALID_FD(fd)			\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		INVALID_FD_FMT,		\
		(fd)			\
	)

/** Writes formatted regcomp error message to `error_buf` */
#define REGCOMP_ERROR(p, e)		\
	regerror(			\
		(e),			\
		(p),			\
		error_buf,		\
		SAFE_SIZE(buf_size)	\
	)

/** Writes formatted file-open failure message to `error_buf` */
#define FILE_OPEN_ERROR(f, e)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		FILE_OPEN_FMT,		\
		(f),			\
		strerror((e))		\
	)

/** Writes formatted file-status failure message to `error_buf` */
#define FILE_STAT_ERROR(f, e)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		FILE_STAT_FMT,		\
		(f),			\
		strerror((e))		\
	)

/** Writes formatted file-open failure message to `error_buf` */
#define FILE_MAP_ERROR(f, e)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		FILE_MAP_FMT,		\
		(f),			\
		strerror((e))		\
	)

/** Writes formatted write syscall failure message to `error_buf` */
#define WRITE_ERROR(fd, e)		\
	snprintf(			\
		error_buf,		\
		SAFE_SIZE(buf_size),	\
		WRITE_FMT,		\
		(fd),			\
		strerror((e))		\
	)

#endif // ISLANDU_LIVECODES_POSIXREGEX_MACROS_H
