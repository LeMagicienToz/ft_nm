#ifndef NM_H
# define NM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include "libft/ft_printf.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <elf.h>
#define EI_CLASS 4  // Offset for ELF class in the header
#define ELFCLASS32 1
#define ELFCLASS64 2

// main
typedef struct s_lst {
    char *str;
    long unsigned int st_value;
    char symb;
    struct s_lst *next;
}t_lst;


void sort_list_ascii(t_lst **head);
t_lst *sort_utf_8(t_lst *lst);
const char *ft_setlocale(int category, const char *locale);
void sort_list_by_str(t_lst **head);
void printer_64(t_lst *list);
void printer_32(t_lst *list);
void list_add_back(t_lst **head, unsigned long addr, char symb, const char *name);
t_lst	*ft_lstnew(void *content);
int checkset_64_32(char *addr, size_t size);
int open_map_binary(const char *path);

//64b

int get_section_64(Elf64_Ehdr *ehdr, char *addr);
char get_symbol_type_64(Elf64_Sym sym, Elf64_Shdr *shdr, char *shstrtab);

//32b

int get_section_32(Elf32_Ehdr *ehdr, char *addr);

#endif