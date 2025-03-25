/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:15:52 by muteza            #+#    #+#             */
/*   Updated: 2021/10/29 15:42:56 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*new;

	if (!lst || !del)
		return (0);
	t = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			while (t)
			{
				new = t->next;
				(*del)(t->content);
				free(t);
				t = new;
			}
		}
		lst = lst->next;
		ft_lstadd_back(&t, new);
	}
	return (t);
}
