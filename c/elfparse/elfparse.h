#ifndef LIVECODES_ELFPARSE_H
#define LIVECODES_ELFPARSE_H

#include <elf.h>
#include <stddef.h>
#include <stdint.h>

/**
 * union elf_hdr_u - Pointer to 32- or 64-bit ELF header structures
 * @v32: Cast as `Elf32_Ehdr *`
 * @v64: Cast as `Elf64_Ehdr *`
 * @raw: Cast as `void *`
 */
typedef union elf_hdr_u {
	Elf32_Ehdr *v32;
	Elf64_Ehdr *v64;
	void *raw;
} elf_hdr_t;

/**
 * union elf_proghdr_u - Pointer to 32- or 64-bit ELF program headers
 * @v32: Cast as `Elf32_Phdr *`
 * @v64: Cast as `Elf64_Phdr *`
 * @raw: Cast as `void *`
 */
typedef union elf_proghdr_u {
	Elf32_Phdr *v32;
	Elf64_Phdr *v64;
	void *raw;
} elf_proghdr_t;

/**
 * union elf_sechdr_u - Pointer to 32- or 64-bit ELF section headers
 * @v32: Cast as `Elf32_Shdr *`
 * @v64: Cast as `Elf64_Shdr *`
 * @raw: Cast as `void *`
 */
typedef union elf_sechdr_u {
	Elf32_Shdr *v32;
	Elf64_Shdr *v64;
	void *raw;
} elf_sechdr_t;

/**
 * uint16fn_t - Pointer to function that returns endian-adjusted 16-bit value
 * @n: Input value
 *
 * Return: Endian-adjusted value
 */
typedef uint16_t (*uint16fn_t)(uint16_t n);

/**
 * uint32fn_t - Pointer to function that returns endian-adjusted 32-bit value
 * @n: Input value
 *
 * Return: Endian-adjusted value
 */
typedef uint32_t (*uint32fn_t)(uint32_t n);

/**
 * uint64fn_t - Pointer to function that returns endian-adjusted 64-bit value
 * @n: Input value
 *
 * Return: Endian-adjusted value
 */
typedef uint64_t (*uint64fn_t)(uint64_t n);

/**
 * struct elf_fmgr_s - ELF file manager structure
 * @elfheader: Pointer to ELF header structure
 * @proghdrs: Pointer to first program header
 * @sechdrs: Pointer to first section header
 * @uint16fn: Pointer to 16-bit endian-adjustment function
 * @uint32fn: Pointer to 32-bit endian-adjustment function
 * @uint64fn: Pointer to 64-bit endian-adjustment function
 * @fsize: Size of ELF file
 * @shstrtab: Pointer to section-header string table
 * @fd: ELF file descriptor
 * @class: `ELFCLASS32` or `ELFCLASS64`
 */
typedef struct elf_fmgr_s {
	elf_hdr_t elfheader;
	elf_proghdr_t proghdrs;
	elf_sechdr_t sechdrs;
	uint16fn_t uint16fn;
	uint32fn_t uint32fn;
	uint64fn_t uint64fn;
	uint64_t fsize;
	char *shstrtab;
	int fd;
	int class;
} elf_fmgr_t;

/**
 * elf_open - Opens an ELF file and initializes `elf_fmgr_t` structure
 * @fpath: Path to ELF file
 *
 * Return: Pointer to ELF file-manager structure
 */
elf_fmgr_t *elf_open(const char *fpath);

/**
 * elf_close - Closes an ELF file and frees `elf_fmgr_t` structure
 * @fmgr: Pointer to ELF file-manager structure
 */
void elf_close(elf_fmgr_t *fmgr);

#define _ELF_VAL16(fmgr, prop) ((fmgr)->uint16fn((fmgr)->prop))
#define _ELF_VAL32(fmgr, prop) ((fmgr)->uint32fn((fmgr)->prop))
#define _ELF_VAL64(fmgr, prop) ((fmgr)->uint64fn((fmgr)->prop))

#define ELF_IDENT_MAGIC(fmgr, i) ((fmgr)->elfheader.v64->e_ident[(i)])
#define ELF_IDENT_CLASS(fmgr) ((fmgr)->elfheader.v64->e_ident[EI_CLASS])
#define ELF_IDENT_DATA(fmgr) ((fmgr)->elfheader.v64->e_ident[EI_DATA])
#define ELF_IDENT_VERSION(fmgr) ((fmgr)->elfheader.v64->e_ident[EI_VERSION])
#define ELF_IDENT_OSABI(fmgr) ((fmgr)->elfheader.v64->e_ident[EI_OSABI])
#define ELF_IDENT_ABIVERSION(fmgr) ((fmgr)->elfheader.v64->e_ident[EI_ABIVERSION])

#define _ELF32_EHDR_PROP16(fmgr, prop) _ELF_VAL16(fmgr, elfheader.v32->prop)
#define _ELF32_EHDR_PROP32(fmgr, prop) _ELF_VAL32(fmgr, elfheader.v32->prop)

#define ELF32_EHDR_TYPE(fmgr) _ELF32_EHDR_PROP16(fmgr, e_type)
#define ELF32_EHDR_MACHINE(fmgr) _ELF32_EHDR_PROP16(fmgr, e_machine)
#define ELF32_EHDR_VERSION(fmgr) _ELF32_EHDR_PROP32(fmgr, e_version)
#define ELF32_EHDR_ENTRY(fmgr) _ELF32_EHDR_PROP32(fmgr, e_entry)
#define ELF32_EHDR_PHOFF(fmgr) _ELF32_EHDR_PROP32(fmgr, e_phoff)
#define ELF32_EHDR_SHOFF(fmgr) _ELF32_EHDR_PROP32(fmgr, e_shoff)
#define ELF32_EHDR_FLAGS(fmgr) _ELF32_EHDR_PROP32(fmgr, e_flags)
#define ELF32_EHDR_EHSIZE(fmgr) _ELF32_EHDR_PROP16(fmgr, e_ehsize)
#define ELF32_EHDR_PHENTSIZE(fmgr) _ELF32_EHDR_PROP16(fmgr, e_phentsize)
#define ELF32_EHDR_PHNUM(fmgr) _ELF32_EHDR_PROP16(fmgr, e_phnum)
#define ELF32_EHDR_SHENTSIZE(fmgr) _ELF32_EHDR_PROP16(fmgr, e_shentsize)
#define ELF32_EHDR_SHNUM(fmgr) _ELF32_EHDR_PROP16(fmgr, e_shnum)
#define ELF32_EHDR_SHSTRNDX(fmgr) _ELF32_EHDR_PROP16(fmgr, e_shstrndx)
#define ELF32_SHSTRTAB_OFFSET(fmgr) _ELF_VAL32(fmgr, sechdrs.v32[ELF32_EHDR_SHSTRNDX(fmgr)].sh_offset)
#define ELF32_PROGRAMHEADERS(fmgr) ((fmgr)->proghdrs.v32)
#define ELF32_SECTIONHEADERS(fmgr) ((fmgr)->sechdrs.v32)

#define _ELF64_EHDR_PROP16(fmgr, prop) _ELF_VAL16(fmgr, elfheader.v64->prop)
#define _ELF64_EHDR_PROP32(fmgr, prop) _ELF_VAL32(fmgr, elfheader.v64->prop)
#define _ELF64_EHDR_PROP64(fmgr, prop) _ELF_VAL64(fmgr, elfheader.v64->prop)

#define ELF64_EHDR_TYPE(fmgr) _ELF64_EHDR_PROP16(fmgr, e_type)
#define ELF64_EHDR_MACHINE(fmgr) _ELF64_EHDR_PROP16(fmgr, e_machine)
#define ELF64_EHDR_VERSION(fmgr) _ELF64_EHDR_PROP32(fmgr, e_version)
#define ELF64_EHDR_ENTRY(fmgr) _ELF64_EHDR_PROP64(fmgr, e_entry)
#define ELF64_EHDR_PHOFF(fmgr) _ELF64_EHDR_PROP64(fmgr, e_phoff)
#define ELF64_EHDR_SHOFF(fmgr) _ELF64_EHDR_PROP64(fmgr, e_shoff)
#define ELF64_EHDR_FLAGS(fmgr) _ELF64_EHDR_PROP32(fmgr, e_flags)
#define ELF64_EHDR_EHSIZE(fmgr) _ELF64_EHDR_PROP16(fmgr, e_ehsize)
#define ELF64_EHDR_PHENTSIZE(fmgr) _ELF64_EHDR_PROP16(fmgr, e_phentsize)
#define ELF64_EHDR_PHNUM(fmgr) _ELF64_EHDR_PROP16(fmgr, e_phnum)
#define ELF64_EHDR_SHENTSIZE(fmgr) _ELF64_EHDR_PROP16(fmgr, e_shentsize)
#define ELF64_EHDR_SHNUM(fmgr) _ELF64_EHDR_PROP16(fmgr, e_shnum)
#define ELF64_EHDR_SHSTRNDX(fmgr) _ELF64_EHDR_PROP16(fmgr, e_shstrndx)
#define ELF64_SHSTRTAB_OFFSET(fmgr) _ELF_VAL64(fmgr, sechdrs.v64[ELF64_EHDR_SHSTRNDX(fmgr)].sh_offset)
#define ELF64_PROGRAMHEADERS(fmgr) ((fmgr)->proghdrs.v64)
#define ELF64_SECTIONHEADERS(fmgr) ((fmgr)->sechdrs.v64)

#endif /* LIVECODES_ELFPARSE_H */
