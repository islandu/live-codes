#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "elfparse.h"

#define OFFSETPTR(ptr, n) ((char *)(ptr) + (n))

static int map_file_mem(elf_fmgr_t *elf_fmgr, const char *fpath);
static int init_elf_props(elf_fmgr_t *elf_fmgr);
static uint16_t le16(uint16_t n);
static uint16_t be16(uint16_t n);
static uint32_t le32(uint32_t n);
static uint32_t be32(uint32_t n);
static uint64_t le64(uint64_t n);
static uint64_t be64(uint64_t n);

/**
 * elf_open - Opens an ELF file and initializes `elf_fmgr_t` structure
 * @fpath: Path to ELF file
 *
 * Return: Pointer to ELF file-manager structure
 */
elf_fmgr_t *elf_open(const char *fpath)
{
	elf_fmgr_t *elf_fmgr = NULL;

	if (!fpath)
		return (NULL);

	/* allocate ELF file manager */
	elf_fmgr = calloc(1, sizeof(elf_fmgr_t));

	if (!elf_fmgr)
		goto alloc_fail;

	/* map ELF file into memory */
	if (map_file_mem(elf_fmgr, fpath) == -1)
		goto map_fail;

	/* parse key components */
	if (init_elf_props(elf_fmgr) == -1)
		goto elf_fail;

	/* success */
	return (elf_fmgr);

elf_fail:
	munmap(elf_fmgr->elfheader.raw, elf_fmgr->fsize);
	close(elf_fmgr->fd);
map_fail:
	free(elf_fmgr);
alloc_fail:
	return (NULL);
}

/**
 * elf_close - Closes an ELF file and frees `elf_fmgr_t` structure
 * @fmgr: Pointer to ELF file-manager structure
 */
void elf_close(elf_fmgr_t *fmgr)
{
	if (!fmgr)
		return;

	/* unmap file memory */
	munmap(fmgr->elfheader.raw, fmgr->fsize);
	/* close file */
	close(fmgr->fd);
	/* free file manager memory */
	free(fmgr);	
}

/**
 * map_file_mem - Uses `mmap` to map ELF file into memory
 * @elf_fmgr: Pointer to ELF file-manager structure
 * @fpath: File path
 *
 * Return: `0` for success, `-1` for failure
 */
static int map_file_mem(elf_fmgr_t *elf_fmgr, const char *fpath)
{
	int fd;
	void *fmem = NULL;
	struct stat statbuf;

	fd = open(fpath, O_RDONLY);

	if (fd == -1)
		goto open_fail;

	if (fstat(fd, &statbuf) == -1)
		goto fstat_fail;

	fmem = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (fmem == MAP_FAILED)
		goto mmap_fail;

	elf_fmgr->elfheader.raw = fmem;
	elf_fmgr->fd = fd;
	elf_fmgr->fsize = statbuf.st_size;

	return (0);

mmap_fail:
fstat_fail:
	close(fd);
open_fail:
	return (-1);
}

/**
 * init_elf_props - Parses/initializes members of ELF file-manager structure
 * @elf_fmgr: Pointer to ELF file-manager structure
 *
 * Return: `0` for success, `-1` for failure
 */
static int init_elf_props(elf_fmgr_t *elf_fmgr)
{
	/* set byte-order functions based on file's endianness */
	switch (elf_fmgr->elfheader.v64->e_ident[EI_DATA]) {
	case ELFDATA2LSB:
		elf_fmgr->uint16fn = le16;
		elf_fmgr->uint32fn = le32;
		elf_fmgr->uint64fn = le64;
		break;
	case ELFDATA2MSB:
		elf_fmgr->uint16fn = be16;
		elf_fmgr->uint32fn = be32;
		elf_fmgr->uint64fn = be64;
		break;
	default:
		return (-1);
	}

	/* retrieving 32/64-bit class */
	elf_fmgr->class = (int)ELF_IDENT_CLASS(elf_fmgr);

	/* set additional pointers based on class */
	switch (elf_fmgr->class) {
	case ELFCLASS32:
		elf_fmgr->proghdrs.raw = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF32_EHDR_PHOFF(elf_fmgr));
		elf_fmgr->sechdrs.raw = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF32_EHDR_SHOFF(elf_fmgr));
		elf_fmgr->shstrtab = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF32_SHSTRTAB_OFFSET(elf_fmgr));
		break;
	case ELFCLASS64:
		elf_fmgr->proghdrs.raw = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF64_EHDR_PHOFF(elf_fmgr));
		elf_fmgr->sechdrs.raw = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF64_EHDR_SHOFF(elf_fmgr));
		elf_fmgr->shstrtab = OFFSETPTR(elf_fmgr->elfheader.raw,
			ELF64_SHSTRTAB_OFFSET(elf_fmgr));
		break;
	default:
		return (-1);
	}

	return (0);
}

/**
 * le16 - Converts 16-bit LE value to host byte order
 * @n: Input value
 *
 * Return: 16-bit value in host byte order
 */
static uint16_t le16(uint16_t n)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	uint16_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}

/**
 * be16 - Converts 16-bit BE value to host byte order
 * @n: Input value
 *
 * Return: 16-bit value in host byte order
 */
static uint16_t be16(uint16_t n)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uint16_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}

/**
 * le32 - Converts 32-bit LE value to host byte order
 * @n: Input value
 *
 * Return: 32-bit value in host byte order
 */
static uint32_t le32(uint32_t n)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	uint32_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[3];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[2];
	((uint8_t *)&result)[2] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[3] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}

/**
 * be32 - Converts 32-bit BE value to host byte order
 * @n: Input value
 *
 * Return: 32-bit value in host byte order
 */
static uint32_t be32(uint32_t n)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uint32_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[3];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[2];
	((uint8_t *)&result)[2] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[3] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}

/**
 * le64 - Converts 64-bit LE value to host byte order
 * @n: Input value
 *
 * Return: 64-bit value in host byte order
 */
static uint64_t le64(uint64_t n)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	uint64_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[7];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[6];
	((uint8_t *)&result)[2] = ((uint8_t *)&n)[5];
	((uint8_t *)&result)[3] = ((uint8_t *)&n)[4];
	((uint8_t *)&result)[4] = ((uint8_t *)&n)[3];
	((uint8_t *)&result)[5] = ((uint8_t *)&n)[2];
	((uint8_t *)&result)[6] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[7] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}

/**
 * be64 - Converts 64-bit BE value to host byte order
 * @n: Input value
 *
 * Return: 64-bit value in host byte order
 */
static uint64_t be64(uint64_t n)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uint64_t result;
	((uint8_t *)&result)[0] = ((uint8_t *)&n)[7];
	((uint8_t *)&result)[1] = ((uint8_t *)&n)[6];
	((uint8_t *)&result)[2] = ((uint8_t *)&n)[5];
	((uint8_t *)&result)[3] = ((uint8_t *)&n)[4];
	((uint8_t *)&result)[4] = ((uint8_t *)&n)[3];
	((uint8_t *)&result)[5] = ((uint8_t *)&n)[2];
	((uint8_t *)&result)[6] = ((uint8_t *)&n)[1];
	((uint8_t *)&result)[7] = ((uint8_t *)&n)[0];
	return (result);
#else
	return (n);
#endif
}
