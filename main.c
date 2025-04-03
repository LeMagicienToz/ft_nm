#include "nm.h"

char get_symbol_type(Elf64_Sym sym, Elf64_Shdr *shdr, char *shstrtab) 
{
char c = '?';

	// 1. IFUNC
	if (ELF64_ST_TYPE(sym.st_info) == STT_GNU_IFUNC) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'i' : 'I';
	}

	// 2. Symbole non défini
	else if (sym.st_shndx == SHN_UNDEF) {
	if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) ? 'v' : 'w';
	} else {
		c = 'U';
	}
	}

	// 3. Symboles spéciaux
	else if (sym.st_shndx == SHN_ABS) {
		c = 'A';
	}
	else if (sym.st_shndx == SHN_COMMON) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'c' : 'C';
	}

	// 4. Symboles définis dans une section
	else if (sym.st_shndx < SHN_LORESERVE) {
		Elf64_Shdr sec = shdr[sym.st_shndx];
		const char *sec_name = shstrtab + sec.sh_name;

		// 4.1 Weak défini
		if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
			c = (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) ? 'V' : 'W';
		}
		// 4.2 Sections de debug
		else if (sec_name && strncmp(sec_name, ".debug", 6) == 0) {
			c = 'N';
		}
		// 4.3 .bss
		else if (sec.sh_type == SHT_NOBITS) {
			c = 'B';
		}
		// 4.4 .dynamic
		else if (sec.sh_type == SHT_DYNAMIC) {
			c = 'D';
		}
		else if (sec.sh_type == SHT_INIT_ARRAY || sec.sh_type == SHT_FINI_ARRAY) {
			c = 'D';
		}
		// 4.5 .text / .data / .rodata
		else if (sec.sh_type == SHT_PROGBITS) {
			if (sec.sh_flags & SHF_EXECINSTR)
				c = 'T';
			else if (sec.sh_flags & SHF_WRITE)
				c = 'D';
			else
				c = 'R';
		}
		// 4.6 Sections lecture seule comme .note, .eh_frame
		else if ((sec.sh_flags & SHF_ALLOC) &&
		         !(sec.sh_flags & SHF_WRITE) &&
		         !(sec.sh_flags & SHF_EXECINSTR)) {
			c = 'R';
		}
		// 4.7 Sections .sdata / .sbss (optionnel)
		else if (sec_name &&
		         (strcmp(sec_name, ".sdata") == 0 || strcmp(sec_name, ".sbss") == 0)) {
			c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'g' : 'G';
		}
	}

	// 5. Mise en minuscule si local (sauf les cas particuliers)
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL &&
	    c != '?' && c != 'U' && c != 'w' && c != 'v')
		c += 32;

	return c;
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

t_lst	*ft_lstnew(void *content)
{
	t_lst	*d;

	d = (t_lst *)malloc(sizeof(t_list));
	if (!d)
		return (NULL);
	d->next = NULL;
	d->str = content;
	return (d);
}

void list_add_back(t_lst **head, unsigned long addr, char symb, const char *name)
{
	t_lst *new = malloc(sizeof(t_lst));
	if (!new)
		return;

	new->st_value = addr;
	new->symb = symb;
	new->str = strdup(name);
	new->next = NULL;

	if (!*head) {
		*head = new;
		return;
	}

	t_lst *tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


int get_section(Elf64_Ehdr *ehdr, char *addr)
{
	Elf64_Shdr *shdr = (Elf64_Shdr *)(addr + ehdr->e_shoff);
	char *shstrtab = addr + shdr[ehdr->e_shstrndx].sh_offset;

	Elf64_Sym *symtab = NULL;
	char *strtab = NULL;
	size_t sym_count = 0;
	size_t strtab_size = 0;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		if (strcmp(&shstrtab[shdr[i].sh_name], ".symtab") == 0) {
			symtab = (Elf64_Sym *)(addr + shdr[i].sh_offset);
			sym_count = shdr[i].sh_size / sizeof(Elf64_Sym);
		}
		else if (strcmp(&shstrtab[shdr[i].sh_name], ".strtab") == 0) {
			strtab = (char *)(addr + shdr[i].sh_offset);
			strtab_size = shdr[i].sh_size;
		}
	}

	if (!symtab || !strtab) {
		return 0;
	}

	t_lst *list = NULL;

	for (size_t i = 0; i < sym_count; i++) {
		uint32_t name_offset = symtab[i].st_name;

		// Vérification sécurité : ne pas lire hors mémoire
		if (name_offset >= strtab_size)
			continue;

		const char *name = &strtab[name_offset];
		if (name[0] == '\0') // ignorer les symboles sans nom
			continue;
		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE)
			continue;

		char type = get_symbol_type(symtab[i], shdr, shstrtab);
		unsigned long addr = symtab[i].st_value;

		// Ajout à la liste
		list_add_back(&list, addr, type, name);
	}
	t_lst *tmp = list;
	int i = 0;
	while (tmp) {
	if (tmp->symb == 'U' || tmp->symb == 'w' || tmp->symb == 'v')
		printf("                 ");
	else
		printf("%016lx ", tmp->st_value);
	printf("%c " ,tmp->symb);
	printf("%s\n", tmp->str);
	tmp = tmp->next;
	i++;
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