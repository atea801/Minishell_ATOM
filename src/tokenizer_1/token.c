/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:39:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 14:40:24 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Set token.value et set avec appel de token_type token.type
 *
 * on passe au token suivant pour etre pret pour le prochain appel
 *
 * @param token
 * @param str
 */
void	put_token(t_token **token, char *res)
{
	(*token)->value = res;
	(*token)->type = get_token_type(res);
	(*token)->next = malloc(sizeof(t_token));
	if (!(*token)->next)
		return ;
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->head = NULL;
	(*token)->type = NULL;
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
 * @brief Envoi chaque mot ou operateur trouve dans un
 * input pour le mettre dans la liste chainee s_token
 *
 * @param token
 * @param str
 */
void	tokenizer(t_token *token, char *str)
{
	int	i;
	int	start;

	i = -1;
	start = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == 39)
		{
			start = i;
			i = skip_quote(str, i);
		}
		if (str[i + 1] == ' ' || str[i + 1] == 0)
		{
			handle_all(&token, str, start, i);
			start = i + 1;
			while (str[start] && str[start] == ' ')
				start++;
		}
	}
}
