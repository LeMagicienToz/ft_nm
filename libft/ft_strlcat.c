/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:49:43 by muteza            #+#    #+#             */
/*   Updated: 2021/10/24 17:18:20 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	j = ft_strlen(dst);
	while (src[i] != '\0' && j + 1 < dstsize)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
/*
int main ()
{
	char dest[] = {"yee"};
	char src[] = {"lorem ipsum dolor sit amet"};
	ft_strlcat(dest,src,15);
	printf("%s\n",dest);
	strlcat(dest,src,15);
	printf("%s\n",dest);
}
*/