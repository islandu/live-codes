#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "fib64/userops.h"

#define FILEDESC_VALID(fd) ((fd) > -1)

static int dev_fd = -1;
static int errno_cache = 0;

int fib64_open(void)
{
	int fd;

	fd = open(FIB64_DEV_PATH, O_RDONLY);
	errno_cache = errno;
	
	if (!FILEDESC_VALID(fd))
		return FIB64_ERROR;

	dev_fd = fd;
	return 0;
}

int fib64_readvals(uint64_t *buf, const size_t count)
{
	ssize_t read_result;

	read_result = read(dev_fd, buf, count << 3);
	errno_cache = errno;
	return read_result < 0 ? FIB64_ERROR : (int)read_result >> 3;
}

int fib64_close(void)
{
	int result;

	result = close(dev_fd);
	errno_cache = errno;
	dev_fd = -1;
	return result;
}

int fib64_errno(void)
{
	return errno_cache;
}
