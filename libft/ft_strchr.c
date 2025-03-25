/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:21:11 by muteza            #+#    #+#             */
/*   Updated: 2021/10/22 20:53:44 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (c == 0)
		return ((char *) s + ft_strlen(s));
	i = -1;
	while (s[++i] && c != 0)
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (NULL);
}
/*
int main()
{
	char str[]={"abccde"};
	int k = '0';
	printf("%s\n",ft_strchr(str, 0));
	//printf("%s",strchr(str, 0));
}
*/