#include "../nm.h"

void printer(t_lst *list)
{
	(void)list;
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

