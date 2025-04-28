#include "../nm.h"

int checkset_64_32(char *addr, size_t size)
{
	if (size < sizeof(Elf64_Ehdr)) {
		printf("File too small to be an ELF\n");
		return -1;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) addr;
	Elf32_Ehdr *ehdr32 = (Elf32_Ehdr *) addr; 

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || 
		ehdr->e_ident[EI_MAG1] != ELFMAG1 || 
		ehdr->e_ident[EI_MAG2] != ELFMAG2 || 
		ehdr->e_ident[EI_MAG3] != ELFMAG3) {
		printf("Not an ELF file\n");
		return -1;
	}
	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
		// printf("ELF is 32-bit (ELF32)\n");
		get_section_32(ehdr32, addr);
		return 32;
	} else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
		// printf("ELF is 64-bit (ELF64)\n");
		get_section_64(ehdr, addr);
		return 64;
	} else {
		printf("Unknown ELF class\n");
		return -1;
	}
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
	// init_char_order();
	if (ac != 2) {
		printf("Usage: %s <elf_file>\n", av[0]);
		return 1;
	}

	return open_map_binary(av[1]) == -1 ? 1 : 0;
}