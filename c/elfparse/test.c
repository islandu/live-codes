
#include <stdio.h>
#include <stdlib.h>
#include "elfparse.h"

static void print_proghdr_types32(elf_fmgr_t *fmgr);
static void print_proghdr_types64(elf_fmgr_t *fmgr);
static void print_sechdr_names32(elf_fmgr_t *fmgr);
static void print_sechdr_names64(elf_fmgr_t *fmgr);
static const char *proghdr_type_desc(uint32_t p_type);

int main(int argc, char **argv)
{
	elf_fmgr_t *elf_file = NULL;

	if (argc != 2)
	{
		fputs("No file provided\n", stderr);
		exit(EXIT_FAILURE);
	}

	elf_file = elf_open(argv[1]);

	if (!elf_file)
	{
		fprintf(stderr, "There was a problem with file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	switch (elf_file->class) {
	case ELFCLASS32:
		print_proghdr_types32(elf_file);
		print_sechdr_names32(elf_file);
		break;
	case ELFCLASS64:
		print_proghdr_types64(elf_file);
		print_sechdr_names64(elf_file);
		break;
	default:
		fputs("Unidentified ELF class\n", stderr);
		elf_close(elf_file);
		exit(EXIT_FAILURE);
	}

	elf_close(elf_file);
	return 0;
}

static void print_proghdr_types32(elf_fmgr_t *fmgr)
{
	uint16_t i;
	Elf32_Phdr *program_headers = NULL;
	const char *desc = NULL;

	program_headers = fmgr->proghdrs.v32;

	for (i = 0; i < ELF32_EHDR_PHNUM(fmgr); ++i)
	{
		desc = proghdr_type_desc(
			fmgr->uint32fn(program_headers[i].p_type));
		printf("Program Header %u: %s\n", i, desc);
	}
}

static void print_proghdr_types64(elf_fmgr_t *fmgr)
{
	uint16_t i;
	Elf64_Phdr *program_headers = NULL;
	const char *desc = NULL;

	program_headers = fmgr->proghdrs.v64;

	for (i = 0; i < ELF64_EHDR_PHNUM(fmgr); ++i)
	{
		desc = proghdr_type_desc(
			fmgr->uint32fn(program_headers[i].p_type));
		printf("Program Header %u: %s\n", i, desc);
	}
}
static void print_sechdr_names32(elf_fmgr_t *fmgr)
{
	uint16_t i;
	Elf32_Shdr *section_headers = NULL;
	const char *name = NULL;

	section_headers = fmgr->sechdrs.v32;

	for (i = 0; i < ELF32_EHDR_SHNUM(fmgr); ++i)
	{
		name = fmgr->shstrtab + fmgr->uint32fn(section_headers[i].sh_name);
		printf("Section header %u: '%s'\n", i, name);
	}
}
static void print_sechdr_names64(elf_fmgr_t *fmgr)
{
	uint16_t i;
	Elf64_Shdr *section_headers = NULL;
	const char *name = NULL;

	section_headers = fmgr->sechdrs.v64;

	for (i = 0; i < ELF64_EHDR_SHNUM(fmgr); ++i)
	{
		name = fmgr->shstrtab + fmgr->uint64fn(section_headers[i].sh_name);
		printf("Section header %u: '%s'\n", i, name);
	}
}

static const char *proghdr_type_desc(uint32_t p_type)
{
	switch (p_type) {
	case PT_LOAD:
		return "Loadable segment";
	case PT_DYNAMIC:
		return "Dynamic-linking information";
	case PT_INTERP:
		return "Interpreter path";
	case PT_NOTE:
		return "Notes";
	case PT_SHLIB:
		return "Shared library (reserved but shouldn't be used)";
	case PT_PHDR:
		return "Location of program header table";
	case PT_GNU_STACK:
		return "GNU stack extension";
	default:
		return "Other/unknown program-segment type";
	}
}
