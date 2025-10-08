/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:21:03 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 16:45:25 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]) && str[i])
		i++;
	return (i);
}

int	calc_res_len_quote(char *str, int i, int *len)
{
	char	quote;

	quote = str[i++];
	(*len)++;
	while (str[i] && str[i] != quote)
	{
		(*len)++;
		i++;
	}
	if (str[i] == quote)
	{
		(*len)++;
		i++;
	}
	return (i);
}

int	calc_res_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i = calc_res_len_quote(str, i, &len);
		else if (is_space(str[i]))
		{
			while (str[i] && is_space(str[i]))
				i++;
			if (str[i])
				len++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
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
		if (str[i] == '"' || str[i] == '\'')
		{
			if (flag && j > 0)
				res[j++] = ' ';
			flag = 0;
			i = copy_quote(str, res, i, &j);
		}
		else if (is_space(str[i]))
			i = skip_and_flag_space(str, i, &flag);
		else
		{
			if (flag && j > 0)
				res[j++] = ' ';
			flag = 0;
			res[j++] = str[i++];
		}
	}
	return (res[j] = '\0', res);
}

/**
 * @brief retire les epaces avant et pendant la chaine de caractere,
 * reecrit la chaine passee en arg et retourne une nouvelle version
 * de cette chaine
 *
 * @param input
 * @return char*
 */
char	*clear_input(char *input)
{
	int		i;
	char	*res;
	int		len;

	i = skip_space(input);
	len = calc_res_len(input, i);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res = epur(input, res, i);
	return (res);
}
