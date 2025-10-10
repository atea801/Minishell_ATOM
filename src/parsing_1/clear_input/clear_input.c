/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:21:03 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 18:27:21 by aautret          ###   ########.fr       */
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

/**
 * @brief Calcule la longueur à ajouter pour une séquence entre quotes.
 * 
 * - Compte le nombre de caractères compris entre les quotes
 *  (y compris les quotes elles-mêmes),
 * 
 * - Incrémente la variable de longueur passée en paramètre
 * 
 * @param str 
 * @param i 
 * @param len 
 * @return int 
 */
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

/**
 * @brief Calcule la longueur de la chaîne épurée sans espaces superflus.
 * 
 * - Compte le nombre de caractères à conserver dans la chaîne résultat
 * 
 * - Supprime les espaces inutiles (sauf à l'intérieur des quotes)
 * 
 * - Laisse qu'un seul espace entre chaque élément
 * 
 * @param str 
 * @param i 
 * @return int 
 */
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
 * @brief Retire les epaces avant et pendant la chaine de caractere,
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
