/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:22:10 by codespace         #+#    #+#             */
/*   Updated: 2025/09/22 15:09:43 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_countword(char const *str, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
		{
			words++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (words);
}

static char	**tab_free(char **tab, size_t j)
{
	while (j--)
		free(tab[j]);
	free(tab);
	return (NULL);
}

static char	**splitter(char const *s, char c, char **tab)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			tab[j] = (char *)malloc(sizeof (char) * (i - start + 1));
			if (!tab[j])
				return (tab_free(tab, j));
			ft_memcpy(tab[j], s + start, i - start);
			tab[j][i - start] = 0;
			j++;
		}
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!tab)
		return (NULL);
	return (splitter(s, c, tab));
}

// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	char	**tab;

// 	tab = ft_split(av[1], av[2][0]);
// 	if (ac == 3)
// 	{
// 		while (*tab)
// 			printf("%s\n", *tab++);
// 	}
// }
