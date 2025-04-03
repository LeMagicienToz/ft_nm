#ifndef NM_H
# define NM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>
#define EI_CLASS 4  // Offset for ELF class in the header
#define ELFCLASS32 1
#define ELFCLASS64 2

typedef struct s_lst {
    char *str;
    long unsigned int st_value;
    char symb;
    struct s_lst *next;
}t_lst;

// typedef struct s_elf32
// {

// }	t_elf32;
void list_add_back(t_lst **head, unsigned long addr, char symb, const char *name);
t_lst	*ft_lstnew(void *content);
int get_section(Elf64_Ehdr *ehdr, char *addr);
int checkset_64_32(char *addr, size_t size);
int open_map_binary(const char *path);

#endif