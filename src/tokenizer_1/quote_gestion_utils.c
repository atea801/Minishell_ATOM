/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:51:09 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 13:53:40 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Permet de trouver la fin d'une quote apres avoir
 * detecter le debut d'une quote
 *
 * - si le caractere a la position i est une double quote on avance
 * jusqu'au prochain guillemet double
 * - si le caractere a la position i est une simple quote on avance
 * jusqu'au prochain guillemet simple
 *
 * @param str
 * @param i
 * @return int index de la quote qui est fermante
 */
int	skip_quote(char *str, int i)
{
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
	}
	if (str[i] == 39)
	{
		i++;
		while (str[i] != 39)
			i++;
	}
	return (i);
}

/**
 * @brief Dettecte si l'element suivant une double quote suivant une simple quote
 * ou si l'element suivant une simple quote suivant une double quote
 *
 * - "' ou '" => return 1
 * @param c
 * @param next
 * @return int
 */
int	quote_state(char c, char next)
{
	if ((c == '"' && next == 39) || (c == 39 && next == '"'))
		return (1);
	return (0);
}
