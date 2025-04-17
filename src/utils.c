#include "../nm.h"
#include "../char_order_utf8.h"

int count_leading_underscores(const char *s) {
    int count = 0;
    while (*s == '_') {
        count++;
        s++;
    }
    return count;
}

int ft_strcmp_nm(const char *a, const char *b) {
    const char *na = a;
    const char *nb = b;

    // Skip leading underscores for comparison
    while (*na == '_') na++;
    while (*nb == '_') nb++;

    while (*na || *nb) {
        unsigned char ca = (unsigned char)*na;
        unsigned char cb = (unsigned char)*nb;

        if (char_order[ca] != char_order[cb])
            return char_order[ca] - char_order[cb];

        na++;
        nb++;
    }

    // Names are equal without underscores, compare underscore count
    int underscores_a = count_leading_underscores(a);
    int underscores_b = count_leading_underscores(b);

    if (underscores_a != underscores_b)
        return underscores_a - underscores_b;

    return 0;
}

int compare_symbols(t_lst *a, t_lst *b) {
    int cmp = ft_strcmp_nm(a->str, b->str);
    if (cmp != 0)
		return cmp;
	if (a->symb != b->symb)
		return (unsigned char)a->symb - (unsigned char)b->symb;
    return 0;
}

void sort_list_by_str(t_lst **head) {
	if (!head || !*head)
		return;

	t_lst *sorted = NULL;

	while (*head) {
		t_lst *curr = *head;
		*head = curr->next;
		curr->next = NULL;

		if (!sorted || compare_symbols(curr, sorted) < 0) {
			// insertion en tête
			curr->next = sorted;
			sorted = curr;
		} else {
			// insertion après
			t_lst *tmp = sorted;
			while (tmp->next && compare_symbols(curr, tmp->next) > 0)
				tmp = tmp->next;

			while (tmp->next && compare_symbols(curr, tmp->next) == 0)
				tmp = tmp->next;

			curr->next = tmp->next;
			tmp->next = curr;
		}
	}

	*head = sorted;
}


void printer(t_lst *list) {
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
