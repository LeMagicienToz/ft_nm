/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argputnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:55:28 by muteza            #+#    #+#             */
/*   Updated: 2021/11/12 07:59:21 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_argputnbr(int n)
{
	int	j;

	j = 0;
	if (n == -2147483648)
	{
		j += ft_argputstr("-2147483648");
		return (j);
	}
	if (n < 0)
	{
		j += ft_argputchar('-');
		n = n * -1;
	}
	if (n <= 9 && n >= 0)
	{
		j += ft_argputchar(n + 48);
	}
	if (n >= 10)
	{
		j += ft_argputnbr(n / 10);
		j += ft_argputnbr(n % 10);
	}
	return (j);
}

/*
int	main(void)
{
	printf("%d\n ", printf(" %d ", -32));
	printf("%d\n ", ft_argputnbr(-32));
}
*/