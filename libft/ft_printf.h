/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:20:59 by muteza            #+#    #+#             */
/*   Updated: 2021/11/12 08:03:20 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>

int		ft_printf(const char *num, ...);
int		ft_checkflags(char **tab_arg, va_list args, int count);
int		ft_check_idflags(int count, char *str);
int		ft_argputstr(char *str);
int		ft_argputchar(int k);
int		ft_argputnbr(int n);
int		ft_argputnbr_base(unsigned long n, int d);

void	ft_putchar(char c);
// void	ft_putstr(char *str);

// char	ft_strlen(char *str);
#endif