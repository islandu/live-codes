#include <limits.h>
#include <stdio.h>
#include "directory_reader.h"

static char PATH_BUF[4096];

const char *dirent_type_name(unsigned char d_type)
{
	switch (d_type) {
	case DT_BLK:
		return "block_device";
	case DT_CHR:
		return "character_device";
	case DT_DIR:
		return "directory";
	case DT_FIFO:
		return "named_pipe";
	case DT_LNK:
		return "symbolic_link";
	case DT_REG:
		return "file";
	case DT_SOCK:
		return "socket";
	default: /* DT_UNKNOWN */
		return "unknown";
	}
}

const char *path_join(const char *dirpath, const char *entry_name)
{
	snprintf(PATH_BUF, PATH_MAX - 1, "%s/%s", dirpath, entry_name);
	return (PATH_BUF);
}
