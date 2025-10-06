/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:32:06 by aautret           #+#    #+#             */
/*   Updated: 2025/10/06 10:54:04 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	count_space(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			count++;
		i++;
	}
	return (count);
}

int	count_words(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;

	while (str[i])
	{
		if (((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z'))
			&& (str[i + 1] == ' ' || str[i + 1] == 0))
				count++;
			i++;
	}
	return (count);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) && str[i])
		i++;
	return (i);
}

/**
 * @brief Permet de skip les espaces a l'interieur d'une chaine de caracteres
 *
 * - skip les espaces en debut et en fin
 *
 * - laisse un seul espace entre chaques elements
 *
 * @param str
 * @param res
 * @param i
 * @return char*
 */
char	*epur(char *str, char *res, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	while (str[i])
	{
		if (is_space(str[i]))
			flag = 1;
		else
		{
			if (flag == 1)
			{
				res[j] = ' ';
				j++;
			}
			flag = 0;
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
