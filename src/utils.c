#include "../nm.h"

int compare_ascii(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (unsigned char)*a - (unsigned char)*b;
}

void insert_sorted(t_lst **sorted, t_lst *new)
{
	t_lst **curr = sorted;

	while (*curr && compare_ascii((*curr)->str, new->str) < 0)
		curr = &(*curr)->next;

	new->next = *curr;
	*curr = new;
}

void sort_list_ascii(t_lst **head)
{
	t_lst *sorted = NULL;
	t_lst *current = *head;
	t_lst *next;

	while (current)
	{
		next = current->next;
		current->next = NULL;
		insert_sorted(&sorted, current);
		current = next;
	}
	*head = sorted;
}

void put_hex_8(unsigned long n)
{
    char hex[9];
    const char *base = "0123456789abcdef";
    int i = 7;

    hex[8] = '\0';
    while (i >= 0) {
        hex[i] = base[n % 16];
        n /= 16;
        i--;
    }
    write(1, hex, 8);
}


void printer_32(t_lst *list) {
	t_lst *tmp = list;
	while (tmp) {
		if (tmp->symb == 'U' || tmp->symb == 'w' || tmp->symb == 'v')
			ft_printf("                 ");
		else
		{
			put_hex_8(tmp->st_value);
			ft_printf(" ");
		}
		ft_printf("%c ", tmp->symb);
		ft_printf("%s", tmp->str);
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void put_hex_16(unsigned long n)
{
    char hex[17];
    const char *base = "0123456789abcdef";
    int i = 15;

    hex[16] = '\0';
    while (i >= 0) {
        hex[i] = base[n % 16];
        n /= 16;
        i--;
    }
    write(1, hex, 16);
}


void printer_64(t_lst *list) {
	t_lst *tmp = list;
	while (tmp) {
		if (tmp->symb == 'U' || tmp->symb == 'w' || tmp->symb == 'v')
			ft_printf("                 ");
		else
		{
			put_hex_16(tmp->st_value);
			ft_printf(" ");
		}
		ft_printf("%c ", tmp->symb);
		ft_printf("%s", tmp->str);
		ft_printf("\n");
		tmp = tmp->next;
	}
}

void list_add_back(t_lst **head, unsigned long addr, char symb, const char *name) {
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

t_lst *ft_lstnew(void *content) {
	t_lst *d = (t_lst *)malloc(sizeof(t_lst));
	if (!d)
		return NULL;
	d->next = NULL;
	d->str = content;
	return d;
}
