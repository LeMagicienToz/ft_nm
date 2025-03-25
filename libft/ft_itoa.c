/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:37:47 by muteza            #+#    #+#             */
/*   Updated: 2021/10/30 13:48:07 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c *= -1;
		i++;
	}
	while (c > 0)
	{
		i++;
		c = c / 10;
	}
	return (i);
}

char	*ft_gest_fill(long n, char *dest, int *i)
{
	if (n > 9)
	{
		ft_gest_fill(n / 10, dest, i);
		ft_gest_fill(n % 10, dest, i);
	}
	else
		dest[(*i)++] = n + 48;
	return (dest);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			i;
	long long	nbr;

	nbr = n;
	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (!dest)
		return (NULL);
	if (n < 0)
	{
		dest[i++] = '-';
		nbr *= -1;
	}
	dest = ft_gest_fill(nbr, dest, &i);
	dest[i] = '\0';
	return (dest);
}
