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
