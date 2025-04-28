#include "../nm.h"

int checkset_64_32(char *addr, size_t size, const char *path)
{
	if (size < sizeof(Elf64_Ehdr)) {
		ft_printf("File too small to be an ELF\n");
		return -1;
	}

	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) addr;
	Elf32_Ehdr *ehdr32 = (Elf32_Ehdr *) addr; 

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || 
		ehdr->e_ident[EI_MAG1] != ELFMAG1 || 
		ehdr->e_ident[EI_MAG2] != ELFMAG2 || 
		ehdr->e_ident[EI_MAG3] != ELFMAG3) {
		ft_printf("Not an ELF file\n");
		return -1;
	}
	else if(ehdr32->e_ident[EI_MAG0] != ELFMAG0 || 
		ehdr32->e_ident[EI_MAG1] != ELFMAG1 || 
		ehdr32->e_ident[EI_MAG2] != ELFMAG2 || 
		ehdr32->e_ident[EI_MAG3] != ELFMAG3) {
		ft_printf("Not an ELF file\n");
		return -1;
	}

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
		// ft_printf("ELF is 32-bit (ELF32)\n");
		if(get_section_32(ehdr32, addr) == 4)
			ft_printf("ft_nm: %s: no symbols\n", path);
		return 32;
	} else if (ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
		// ft_printf("ELF is 64-bit (ELF64)\n");
		if(get_section_64(ehdr, addr) == 4)
			ft_printf("ft_nm: %s: no symbols\n", path);
		return 64;
	} else {
		ft_printf("Unknown ELF class\n");
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
		ft_printf("File is empty\n");
		close(fd);
		return -1;
	}

	char *addr = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	if (addr == MAP_FAILED) {
		perror("Error mapping file");
		return -1;
	}

	int result = checkset_64_32(addr, statbuf.st_size, path);
	munmap(addr, statbuf.st_size);
	return result;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		ft_printf("Usage: %s <elf_file>\n", av[0]);
		return 1;
	}

	return open_map_binary(av[1]) == -1 ? 1 : 0;
}