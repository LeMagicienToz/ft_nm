/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:23:37 by muteza            #+#    #+#             */
/*   Updated: 2021/10/25 11:43:42 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	j = ft_strlen(s1);
	i = 0;
	str = malloc(ft_strlen(s2 + j));
	if (!s1 && !s2)
		return (NULL);
	if(!s1)
		return (s2);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	return (str);
}
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		lens1;
	int		lens2;
	char	*str;

	if (s1 && s2)
	{
		lens1 = ft_strlen(s1);
		lens2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[lens1] = s2[i];
			lens1++;
		}
		str[lens1] = '\0';
		return (str);
	}
	return (NULL);
}
/*
int main()
{
	char	s1[] = "tripouille ";
	char	s2[] = "l'ananas";
	printf(ft_strjoin(s1,s2));
}
*/