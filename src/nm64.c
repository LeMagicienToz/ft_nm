#include "../nm.h"

char get_symbol_type_64(Elf64_Sym sym, Elf64_Shdr *shdr, char *shstrtab) 
{
char c = '?';

	// 1. IFUNC
	if (ELF64_ST_TYPE(sym.st_info) == STT_GNU_IFUNC) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'i' : 'I';
	}

	// 2. Symbole non defini
	else if (sym.st_shndx == SHN_UNDEF) {
	if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) ? 'v' : 'w';
	} else {
		c = 'U';
	}
	}

	// 3. Symboles speciaux
	else if (sym.st_shndx == SHN_ABS) {
		c = 'A';
	}
	else if (sym.st_shndx == SHN_COMMON) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'c' : 'C';
	}

	// 4. Symboles definis dans une section
	else if (sym.st_shndx < SHN_LORESERVE) {
		Elf64_Shdr sec = shdr[sym.st_shndx];
		const char *sec_name = shstrtab + sec.sh_name;
		// 4.1 Weak defini
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
		else if (sec.sh_type == SHT_DYNAMIC
			|| sec.sh_type == SHT_INIT_ARRAY
			|| sec.sh_type == SHT_FINI_ARRAY
			|| sec.sh_type == SHT_PREINIT_ARRAY) {
			c = 'D';
		}
		// 4.5 .text / .data / .rodata
		else if (sec.sh_type == SHT_PROGBITS) {
			// printf("\nouiii\n");
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
		         (ft_strcmp(sec_name, ".sdata") == 0 || ft_strcmp(sec_name, ".sbss") == 0)) {
			c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'g' : 'G';
		}
	}

	// 5. Mise en minuscule si local (sauf les cas particuliers)
	if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL &&
	    c != '?' && c != 'U' && c != 'w' && c != 'v')
		c += 32;

	return c;
}



int get_section_64(Elf64_Ehdr *ehdr, char *addr)
{
	Elf64_Shdr *shdr = (Elf64_Shdr *)(addr + ehdr->e_shoff);
	char *shstrtab = addr + shdr[ehdr->e_shstrndx].sh_offset;

	Elf64_Sym *symtab = NULL;
	char *strtab = NULL;
	size_t sym_count = 0;
	size_t strtab_size = 0;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		if (ft_strcmp(&shstrtab[shdr[i].sh_name], ".symtab") == 0) {
			symtab = (Elf64_Sym *)(addr + shdr[i].sh_offset);
			sym_count = shdr[i].sh_size / sizeof(Elf64_Sym);
		}
		else if (ft_strcmp(&shstrtab[shdr[i].sh_name], ".strtab") == 0) {
			strtab = (char *)(addr + shdr[i].sh_offset);
			strtab_size = shdr[i].sh_size;
		}
	}

	if (!symtab || !strtab) {
		return 4;
	}

	t_lst *list = NULL;

	for (size_t i = 0; i < sym_count; i++) {
		uint32_t name_offset = symtab[i].st_name;

		// Verif securite : ne pas lire hors memoire
		if (name_offset >= strtab_size)
			continue;

		const char *name = &strtab[name_offset];
		if (name[0] == '\0') // ignorer les symboles sans nom
			continue;
		if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FILE)
			continue;
		char type = get_symbol_type_64(symtab[i], shdr, shstrtab);
		unsigned long addr = symtab[i].st_value;
		list_add_back(&list, addr, type, name);
        }
		// setlocale(LC_COLLATE, ""); //active les regles pour strcoll
		sort_list_ascii(&list);
        printer_64(list);
		freelist(list);
	return(0);
}
