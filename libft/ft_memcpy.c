/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:55:00 by muteza            #+#    #+#             */
/*   Updated: 2021/10/26 14:06:33 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t	n)
{
	size_t	i;
	char	*s1;

	s1 = (char *)dst;
	i = 0;
	if (!src && !dst)
		return (0);
	while (i < n)
	{
		*(char *)s1 = *(char *)src;
		s1++;
		src++;
		i++;
	}
	return (dst);
}
/*
int main ()
{
    char dst[] = {"\0"};
    char src[] = {"12"};
    //printf(ft_memcpy(dst,src,1));
    printf(memcpy(dst,src,1));
}
*/