/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argputnbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:59:53 by muteza            #+#    #+#             */
/*   Updated: 2021/11/11 17:32:35 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_argputnbr_base(unsigned long n, int d)
{
	char			*base;
	char			c;
	int				j;
	unsigned int	k;

	j = 0;
	if (d == 0)
		base = "0123456789abcdef";
	if (d == 1)
		base = "0123456789ABCDEF";
	if (d == 2)
		base = "0123456789";
	k = ft_strlen(base);
	if (n >= k)
	{
		j += ft_argputnbr_base((n / k), d);
		j += ft_argputnbr_base((n % k), d);
	}
	if (n < k)
	{
		c = base[n];
		j += ft_argputchar(c);
	}
	return (j);
}
/*
int main()
{
	printf("%d\n ", printf("%x", 16));
	printf("%d\n ", ft_argputnbr_base(16, 16));
}
*/