#include "nm.h"

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
	printf("%s\n", &shstrtab[shdr[3].sh_name]);
	
	Elf64_Sym *symtab = NULL;
	char *strtab = NULL;
	size_t sym_count = 0;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		if (strcmp(&shstrtab[shdr[i].sh_name], ".symtab") == 0) {
			printf("\n\n%d\n\n", i);
			symtab = (Elf64_Sym *)(addr + shdr[i].sh_offset);
			sym_count = shdr[i].sh_size / sizeof(Elf64_Sym);
		} else if (strcmp(&shstrtab[shdr[i].sh_name], ".strtab") == 0) {
			strtab = (char *)(addr + shdr[i].sh_offset);
		}
	}
	for (size_t i = 0; i < sym_count; i++) {
		if (symtab[i].st_name != 0) {
			// printf("%lx %c %s\n", symtab[i].st_value, (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC) ? 'T' : '?', );
			printf("%.16lx           ",  symtab[i].st_value);
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
	
	// Affichage de la signature ELF en hexadécimal (ELF au debut)
	printf("ELF Magic: %02x %02x %02x %02x\n",
		   addr[0] & 0xff, addr[1] & 0xff, addr[2] & 0xff, addr[3] & 0xff);
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