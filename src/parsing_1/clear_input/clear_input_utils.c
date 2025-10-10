/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:32:06 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 18:28:58 by aautret          ###   ########.fr       */
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
		if (((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z')) && (str[i + 1] == ' '
				|| str[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

int	copy_quote(char *str, char *res, int i, int *j)
{
	char	quote;

	quote = str[i++];
	res[(*j)++] = quote;
	while (str[i] && str[i] != quote)
		res[(*j)++] = str[i++];
	if (str[i] == quote)
		res[(*j)++] = str[i++];
	return (i);
}

/**
 * @brief Ignore les espaces consécutifs et active un flag pour 
 * signaler un espace à ajouter.
 *
 * - Avance l'index dans la chaîne tant qu'il y a des espaces
 * 
 * - Active le flag pour indiquer qu'un espace doit être ajouté dans la chaîne 
 * résultat
 * 
 * @param str 
 * @param i 
 * @param flag 
 * @return int 
 */
int	skip_and_flag_space(char *str, int i, int *flag)
{
	while (str[i] && is_space(str[i]))
		i++;
	*flag = 1;
	return (i);
}
