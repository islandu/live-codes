#ifndef ISLANDU_LIVECODES_LKM_FIB64_USEROPS_H
#define ISLANDU_LIVECODES_LKM_FIB64_USEROPS_H

#include <stddef.h>
#include <stdint.h>

#define FIB64_DEV_PATH "/dev/fib64"
#define FIB64_ERROR -1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * fib64_open
 */
int fib64_open(void);

/**
 * fib64_readvals
 */
int fib64_readvals(uint64_t *buf, const size_t count);

/**
 * fib64_release
 */
int fib64_close(void);

/**
 * fib64_errno
 */
int fib64_errno(void);

#ifdef __cplusplus
}
#endif

#endif /* ISLANDU_LIVECODES_LKM_FIB64_USEROPS_H */
