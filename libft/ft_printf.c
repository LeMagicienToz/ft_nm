/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:43:43 by muteza            #+#    #+#             */
/*   Updated: 2021/11/12 08:03:17 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *num, ...)
{
	int		count;
	int		compteur;
	va_list	argument;

	compteur = 0;
	count = 0;
	va_start(argument, num);
	while (num[count] != '\0')
	{
		if (num[count] == '%' && ft_check_idflags(count, (char *)num) == 1)
		{
			count++;
			compteur += ft_checkflags((char **)&num, argument, count);
			count++;
		}
		else if (num[count] != '%')
		{
			ft_putchar(num[count]);
			compteur++;
			count++;
		}
	}
	va_end(argument);
	return (compteur);
}

/*
int	main(void)
{
	char	c;

	printf("%d\n", printf(" %p  ", &c));
	printf("%d\n", ft_printf(" %p  ", &c));
}
*/