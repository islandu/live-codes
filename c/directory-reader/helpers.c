#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include "directory_reader.h"

static char PATH_BUF[PATH_MAX];
static char PERMS_ALPHAMAP[3] = { 'r', 'w', 'x' };
static char FTYPE_ALPHAMAP[16] = {
	'?', 'p', 'c', '?',
	'd', '?', 'b', '?',
	'-', '?', 'l', '?',
	's', '?', '?', '?'
};

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
	snprintf(PATH_BUF, PATH_MAX, "%s/%s", dirpath, entry_name);
	return (PATH_BUF);
}

int mode_to_str(char *buf, mode_t mode)
{
	mode_t pmask, i;

	/* maps the file-type bits to a value 0-15 */
	*buf++ = FTYPE_ALPHAMAP[(mode & S_IFMT) >> 12];

	/* masks read permissions of owner first */
	pmask = S_IRUSR;

	/**
	 * check each permission bit and map to alpha code
	 * owner:  i = 0-2 (rwx)
	 * group:  i = 3-5 (rwx)
	 * others: i = 6-8 (rwx)
	 */
	for (i = 0; i < 9; ++i, pmask >>= 1)
		*buf++ = (mode & pmask) ? PERMS_ALPHAMAP[i % 3] : '-';

	*buf = '\0';

	return (0);
}

int longlistfmt_init(longlistfmt_t *longlist,
		     const char *entry_name,
		     struct stat *statbuf)
{
	struct passwd *pwd = NULL;
	struct group *group = NULL;

	mode_to_str(longlist->mode, statbuf->st_mode);
	longlist->nlinks = statbuf->st_nlink;

	pwd = getpwuid(statbuf->st_uid);
	group = getgrgid(statbuf->st_gid);

	if (!pwd || !group)
		return (-1);

	longlist->user = pwd->pw_name;
	longlist->group = group->gr_name;
	longlist->size = statbuf->st_size;
	longlist->modified = ctime(&(statbuf->st_mtime));
	longlist->entry_name = entry_name;
	return (0);
}

void longlistfmt_print(longlistfmt_t *longlist)
{
	/* mode nlink user group size modified entry_name */
	printf("%s %lu %s %s %-4lu %.12s %s\n",
	       longlist->mode,
	       longlist->nlinks,
	       longlist->user,
	       longlist->group,
	       longlist->size,
	       /* trimming the \n off of ctime string */
	       longlist->modified + 4,
	       longlist->entry_name
	);
}
