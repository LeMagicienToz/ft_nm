/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:44:22 by muteza            #+#    #+#             */
/*   Updated: 2021/11/02 17:08:20 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = -1;
	if (n == 0)
		return (0);
	while (++i < n - 1 && *c1 == *c2)
	{
		c1++;
		c2++;
	}
	return (*c1 - *c2);
}
/*
int main()
{	
	char s1[] = {0, 0, 127, 0};
	char s2[] = {"\200", 0, 42, 0};
	printf("%d\n", ft_memcmp(s1, s2, 2));
	printf("%d\n", memcmp(s1, s2, 2));
}
*/