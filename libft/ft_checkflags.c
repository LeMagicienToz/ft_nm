/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkflags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:18:33 by muteza            #+#    #+#             */
/*   Updated: 2021/11/12 07:57:07 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checkflags(char **tab_arg, va_list args, int count)
{
	if (*(tab_arg[0] + count) == 'c')
		return (ft_argputchar(va_arg(args, int)));
	if (*(tab_arg[0] + count) == 's')
		return (ft_argputstr(va_arg(args, char *)));
	if (*(tab_arg[0] + count) == 'p')
	{
		ft_argputstr("0x");
		return (ft_argputnbr_base(va_arg(args, unsigned long), 0) + 2);
	}
	if ((*(tab_arg[0] + count) == 'd') || (*(tab_arg[0] + count) == 'i'))
		return (ft_argputnbr(va_arg(args, int)));
	if (*(tab_arg[0] + count) == 'u')
		return (ft_argputnbr_base(va_arg(args, unsigned int), 2));
	if (*(tab_arg[0] + count) == 'x')
		return (ft_argputnbr_base(va_arg(args, unsigned int), 0));
	if (*(tab_arg[0] + count) == 'X')
		return (ft_argputnbr_base(va_arg(args, unsigned int), 1));
	if (*(tab_arg[0] + count) == '%')
		return (ft_argputchar('%'));
	return (0);
}

int	ft_check_idflags(int count, char *str)
{
	int		i;
	char	*flags;

	flags = "scdiuxXp%";
	i = 0;
	count++;
	while (flags[i] != str[count] && flags[i])
		i++;
	if (flags[i] == str[count])
		return (1);
	else
		return (0);
}
