#include "../nm.h"
// #include <string.h>

int compare_symbols(t_lst *a, t_lst *b) {
	int cmp = strcoll(a->str, b->str);  // respecte le tri local de nm
	if (cmp != 0)
		return cmp;
	if (a->st_value < b->st_value)
		return -1;
	if (a->st_value > b->st_value)
		return 1;
	return 0;
}


void sort_list_by_str(t_lst **head) {
	if (!head || !*head)
		return;

	t_lst *sorted = NULL;

	while (*head) {
		t_lst *curr = *head;
		*head = curr->next;

		if (!sorted || compare_symbols(curr, sorted) < 0) {
			curr->next = sorted;
			sorted = curr;
		} else {
			t_lst *tmp = sorted;
			while (tmp->next && compare_symbols(curr, tmp->next) > 0)
				tmp = tmp->next;

			curr->next = tmp->next;
			tmp->next = curr;
		}
	}
	*head = sorted;
}




void printer(t_lst *list)
{
	t_lst *tmp = list;
	while (tmp) {
		if (tmp->symb == 'U' || tmp->symb == 'w' || tmp->symb == 'v')
			printf("                 ");
		else
			printf("%016lx ", tmp->st_value);

		printf("%c ", tmp->symb);
		printf("%s", tmp->str);
		printf("\n");
		tmp = tmp->next;
	}
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

