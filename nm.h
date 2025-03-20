#ifndef NM_H
# define NM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/stat.h>
#include <unistd.h>
#include <elf.h>
#define EI_CLASS 4  // Offset for ELF class in the header
#define ELFCLASS32 1
#define ELFCLASS64 2

// typedef struct s_elf32
// {

// }	t_elf32;

int get_section(Elf64_Ehdr *ehdr, char *addr);
int checkset_64_32(char *addr, size_t size);
int open_map_binary(const char *path);

#endif