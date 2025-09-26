/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:35:21 by aautret           #+#    #+#             */
/*   Updated: 2025/09/26 18:05:02 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Dettecte si l'element suivant une double quote suivant une simple quote /
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

/**
 * @brief Permet de trouver la fin d'une quote apres avoir 
 * detecter le debut d'une quote
 *
 * - si le caractere a la position i est une double quote on avance jusqu'au prochain guillemet double
 * - si le caractere a la position i est une simple quote on avance jusqu'au prochain guillemet simple
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
 * @brief Utiliser quand on detecte des cas speciaux "' ou '"
 le texte entre le quotes est copie mais pas les quotes exterieurs
 *
 *
 * == extraire dans les cas speciaux "' ou '" => on copie la sous chaine avec les quotes
 * ("'hello'" => 'hello')
 * @param token
 * @param str
 * @param start
 * @param end
 */
void	handle_quote_state(t_token **token, char *str, int *start, int end)
{
	char	*res;

	res = malloc_token(end, *start);
	copy_word(res, str, end, *start);
	put_token(token, res);
}

/**
 * @brief Permet d'isoler et de stocker le mot entre guillemets, on inclue pas les guillemets dans le token
 *


 * == extraire le texte situe a l'interieur des quotes simple ou double sans inclures les quotes dans le token
 * @param token
 * @param str
 * @param start
 * @param end
 */
void	handle_quote(t_token **token, char *str, int *start, int end)
{
	char	*res;

	res = malloc_token(end, *start + 1);
	copy_word(res, str, end, *start + 1);
	put_token(token, res);
	(*start) += 1;
}

/**
 * @brief Gere les cas normaux qui ne sont pas entre des quotes
 *
 * @param token
 * @param str
 * @param start
 * @param end
 */
void	handle_general(t_token **token, char *str, int *start, int i)
{
	char	*res;

	res = malloc_token(i, *start);
	copy_word(res, str, i, *start);
	put_token(token, res);
	(*start) = i + 1;
}

/**
 * @brief Permet de choisir comment tokeniser en fonction de si o
 *
 * - cas special "' ou '" == handle_quote_state
 * - cas mots entre quotes similaires simple ou double == handle_quote
 * - cas mots normaux == handle_general
 * 
 *
 * @param token
 * @param str
 * @param start
 * @param end
 */
void	handle_all(t_token **token, char *str, int start, int i)
{
	if ((str[start] == '"' && str[start + 1] == 39)
		|| (str[start] == 39 && str[start + 1] == '"'))
	{
		start = start + 1;
		handle_quote_state(token, str, &start, i - 1);
	}
	else
	{
		if (str[i] == '"' || str[i] == 39)
			handle_quote(token, str, &start, i - 1);
		else
			handle_general(token, str, &start, i);
	}
}
