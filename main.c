#include "nm.h"


// #define STT_NOTYPE	0		/* Symbol type is unspecified */
// #define STT_OBJECT	1		/* Symbol is a data object */
// #define STT_FUNC	2		/* Symbol is a code object */
// #define STT_SECTION	3		/* Symbol associated with a section */
// #define STT_FILE	4		/* Symbol's name is file name */
// #define STT_COMMON	5		/* Symbol is a common data object */
// #define STT_TLS		6		/* Symbol is thread-local data object*/
// #define	STT_NUM		7		/* Number of defined types.  */
// #define STT_LOOS	10		/* Start of OS-specific */
// #define STT_GNU_IFUNC	10		/* Symbol is indirect code object */
// #define STT_HIOS	12		/* End of OS-specific */
// #define STT_LOPROC	13		/* Start of processor-specific */
// #define STT_HIPROC	15		/* End of processor-specific */

char get_symbol_type(Elf64_Sym sym, Elf64_Shdr *shdr) {
	// 	char type = 'U';

	(void)sym;
	(void)shdr;
	// if (ELF64_ST_TYPE(sym.st_info) == STT_FUNC)
	return ('?');
	
}


int checkset_64_32(char *addr, size_t size)
{
	if (size < sizeof(Elf64_Ehdr)) {
		printf("File too small to be an ELF\n");
		return -1;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) addr;

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || 
		ehdr->e_ident[EI_MAG1] != ELFMAG1 || 
		ehdr->e_ident[EI_MAG2] != ELFMAG2 || 
		ehdr->e_ident[EI_MAG3] != ELFMAG3) {
		printf("Not an ELF file\n");
		return -1;
	}

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
		printf("ELF is 32-bit (ELF32)\n");
		return 32;
	} else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
		printf("ELF is 64-bit (ELF64)\n");
		get_section(ehdr, addr);
		return 64;
	} else {
		printf("Unknown ELF class\n");
		return -1;
	}
}

int get_section(Elf64_Ehdr *ehdr, char *addr)
{
	Elf64_Shdr *shdr = (Elf64_Shdr *)(addr + ehdr->e_shoff); // pointe vers le debut de la table des section
	char *shstrtab = addr + shdr[ehdr->e_shstrndx].sh_offset; // section qui contien le nom des section
	
	Elf64_Sym *symtab = NULL;
	char *strtab = NULL;
	size_t sym_count = 0;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		if (strcmp(&shstrtab[shdr[i].sh_name], ".symtab") == 0) 
		{
			symtab = (Elf64_Sym *)(addr + shdr[i].sh_offset);
			sym_count = shdr[i].sh_size / sizeof(Elf64_Sym);
		} 
		else if (strcmp(&shstrtab[shdr[i].sh_name], ".strtab") == 0) 
		{
			strtab = (char *)(addr + shdr[i].sh_offset);
		}
		else if (strcmp(&shstrtab[shdr[i].sh_name], ".dynsym") == 0)
		{
			continue ;
		}
	}
	for (size_t i = 0; i < sym_count; i++) {
		if (symtab[i].st_name != 0) {
			// printf("%lx %c %s\n", symtab[i].st_value, (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC) ? 'T' : '?', );
			printf("%.16lx ",  symtab[i].st_value);
			printf("%c ",	get_symbol_type(symtab[i], shdr));
			printf("%s\n", &strtab[symtab[i].st_name]);
		}
	}

	return(0);
}

int open_map_binary(const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("Error opening file");
		return -1;
	}

	struct stat statbuf;
	if (fstat(fd, &statbuf) == -1) {
		perror("Error getting file stats");
		close(fd);
		return -1;
	}

	if (statbuf.st_size == 0) {
		printf("File is empty\n");
		close(fd);
		return -1;
	}

	char *addr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);  // On peut fermer le fichier après mmap

	if (addr == MAP_FAILED) {
		perror("Error mapping file");
		return -1;
	}

	int result = checkset_64_32(addr, statbuf.st_size);
	munmap(addr, statbuf.st_size);
	return result;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("Usage: %s <elf_file>\n", av[0]);
		return 1;
	}

	return open_map_binary(av[1]) == -1 ? 1 : 0;
}