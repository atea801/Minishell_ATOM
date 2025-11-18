/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:34:48 by aautret           #+#    #+#             */
/*   Updated: 2025/11/18 14:39:38 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief copie le mot dectecter pour future tokenisation
 * (gain de lignes pour la norme)
 *
 * @param res
 * @param str
 * @param end
 * @param start
 */
void	copy_word(char *res, char *str, int end, int start)
{
	int	j;
	int	k;

	j = 0;
	k = start;
	while (k <= end)
		res[j++] = str[k++];
	res[j] = 0;
}


/**
 * @brief Set token.value et set avec appel de token_type token.type
 *
 * on passe au token suivant pour etre pret pour le prochain appel
 *
 * @param token
 * @param str
 * @note ajout de l'initialisation de qote_type
 */
int	put_token(t_token **token, char *res)
{
	(*token)->value = res;
	(*token)->type = get_token_type(res);
	(*token)->next = malloc(sizeof(t_token));
	if (!(*token)->next)
		return (1);
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->head = NULL;
	(*token)->type = NULL;
	(*token)->quote_type = 0;
	return (0);
}

/**
 * @brief Set token.value, token.type et token.quote_type, 
 * puis passe au token suivant
 * 
 * Version moderne qui gère les quotes directement sans marqueurs
 *
 * @param token
 * @param res
 * @param quote_type 0=normal, 1=single_quote, 2=double_quote
 * @note // Initialisation quote_type
 */
int	put_token_with_quote(t_token **token, char *res, int quote_type)
{
	(*token)->value = res;
	(*token)->type = get_token_type(res);
	(*token)->quote_type = quote_type;
	(*token)->next = malloc(sizeof(t_token));
	if (!(*token)->next)
		return (1);
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->head = NULL;
	(*token)->type = NULL;
	(*token)->quote_type = 0;
	return (0);
}

/**
 * @brief allocation de memoire pour tokenizer
 * (gain de lignes pour la norme)
 *
 * @param end
 * @param start
 * @return char*
 */
char	*malloc_token(int end, int start)
{
	char	*res;

	res = malloc(sizeof(char) * (end - start + 2));
	if (!res)
		return (NULL);
	return (res);
}
