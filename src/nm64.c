#include "../nm.h"
#include <locale.h>

const char *get_system_locale(void) {
	const char *locale;

	if ((locale = getenv("LC_ALL")) && *locale)
		return locale;
	if ((locale = getenv("LC_COLLATE")) && *locale)
		return locale;
	if ((locale = getenv("LANG")) && *locale)
		return locale;
	return "C"; // fallback
}


char get_symbol_type_64(Elf64_Sym sym, Elf64_Shdr *shdr, char *shstrtab) 
{
	char c = '?';

	//IFUNC
	if (ELF64_ST_TYPE(sym.st_info) == STT_GNU_IFUNC) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'i' : 'I';
	}

	//Symbole non defini
	else if (sym.st_shndx == SHN_UNDEF) {
	if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		c = (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) ? 'v' : 'w';
	} else {
		c = 'U';
	}
	}

	//Symboles speciaux
	else if (sym.st_shndx == SHN_ABS) {
		c = 'A';
	}
	else if (sym.st_shndx == SHN_COMMON) {
		c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'c' : 'C';
	}

	//Symboles definis dans une section
	else if (sym.st_shndx < SHN_LORESERVE) {
		Elf64_Shdr sec = shdr[sym.st_shndx];
		const char *sec_name = shstrtab + sec.sh_name;

		//Weak defini
		if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
			c = (ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) ? 'V' : 'W';
		}
		//Sections de debug
		else if (sec_name && strncmp(sec_name, ".debug", 6) == 0) {
			c = 'N';
		}
		//.bss
		else if (sec.sh_type == SHT_NOBITS) {
			c = 'B';
		}
		//.dynamic
		else if (sec.sh_type == SHT_DYNAMIC) {
			c = 'D';
		}
		else if (sec.sh_type == SHT_INIT_ARRAY || sec.sh_type == SHT_FINI_ARRAY) {
			c = 'D';
		}
		//Section .text / .data / .rodata
		else if (sec.sh_type == SHT_PROGBITS) {
			if (sec.sh_flags & SHF_EXECINSTR)
				c = 'T';
			else if (sec.sh_flags & SHF_WRITE)
				c = 'D';
			else
				c = 'R';
		}
		//Section lecture seule comme .note, .eh_frame
		else if ((sec.sh_flags & SHF_ALLOC) &&
				 !(sec.sh_flags & SHF_WRITE) &&
				 !(sec.sh_flags & SHF_EXECINSTR)) {
			c = 'R';
		}
		//Section .sdata / .sbss (optionnel)
		else if (sec_name &&
				 (strcmp(sec_name, ".sdata") == 0 || strcmp(sec_name, ".sbss") == 0)) {
			c = (ELF64_ST_BIND(sym.st_info) == STB_LOCAL) ? 'g' : 'G';
		}
	}

	// minuscule si local (sauf les cas particuliers)
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
		// sort_list_by_str(&list);
		printer_64(list);
	return(0);
}
