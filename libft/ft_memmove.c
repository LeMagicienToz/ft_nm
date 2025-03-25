/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:34:50 by muteza            #+#    #+#             */
/*   Updated: 2021/10/27 17:50:55 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	int		i;
	char	*s1;
	char	*d1;

	if (src == NULL && dest == NULL)
		return (NULL);
	s1 = (char *)src;
	d1 = (char *)dest;
	i = 0;
	if (s1 < d1)
	{
		while (len > 0)
		{
			d1[len - 1] = s1[len - 1];
			len--;
		}
	}
	while (0 < len)
	{
		d1[i] = s1[i];
		i++;
		len--;
	}
	return (dest);
}
/*
int main ()
{
	char t[] = {"abcdefgh"};
	char g[] = {"abcdefgh"};

    char src[] = {"AKKllll"};
    char dst[] = {"BCDEF"};
    printf("%s\n",ft_memmove(t + 2,t + 1,4));
    printf("%s\n",memmove(g + 2,g + 1, 4));
//	printf("%s\n",memcpy(t + 2,t + 1,8));
}
*/