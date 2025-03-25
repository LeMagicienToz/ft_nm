/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:43:24 by muteza            #+#    #+#             */
/*   Updated: 2021/10/22 14:58:52 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned int	i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char )c)
		{
			return ((void *)s + i);
		}
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char str[]= {0, 1, 2, 3, 4, 5};
	//int k = 0;
	printf("%s\n",ft_memchr(str, 0, 1));
	//printf("%s",memchr(str, 0, 1));
}
*/