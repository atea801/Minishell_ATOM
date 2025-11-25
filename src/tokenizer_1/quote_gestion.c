/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:35:21 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 16:15:34 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Utiliser quand on detecte des cas speciaux "' ou '"
 le texte entre le quotes est copie mais pas les quotes exterieurs
 *
 * == extraire dans les cas speciaux "' ou '" => on copie la sous
 * chaine avec les quotes
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
 * @brief Permet d'isoler et de stocker le mot entre guillemets,
 * on inclue pas les guillemets dans le token
 *
 *
 * == extraire le texte situe a l'interieur des quotes simple
 * ou double sans inclures les quotes dans le token
 * @param token
 * @param str
 * @param start
 * @param end
 */
int	handle_quote(t_token **token, char *str, int *start, int end)
{
	char	*res;
	int		quote_type;

	res = malloc_token(end, *start + 1);
	if (!res)
		return (1);
	copy_word(res, str, end, *start + 1);
	if (str[*start] == '\'')
		quote_type = 1;
	else if (str[*start] == '"')
		quote_type = 2;
	else
		quote_type = 0;
	if (put_token_with_quote(token, res, quote_type))
		return (free(res), 1);
	(*start) += 1;
	return (0);
}

static void	handle_general_utils(char *res, t_token **token)
{
	char	*first_token;
	char	*remaining;

	first_token = ft_strdup("$?");
	remaining = ft_strdup(res + 2);
	put_token(token, first_token);
	put_token(token, remaining);
	free(res);
}

/**
 * @brief Gere les cas normaux qui ne sont pas entre des quotes
 * Sépare spécialement $?$ en deux tokens : $? et $
 *
 * @param token
 * @param str
 * @param start
 * @param end
 */
void	handle_general(t_token **token, char *str, int *start, int i)
{
	char	*res;
	int		j;

	if (*start > i)
		return ;
	res = malloc_token(i, *start);
	copy_word(res, str, i, *start);
	j = 0;
	while (res[j] && res[j] == ' ')
		j++;
	if (res[j] == '\0')
	{
		(*start) = i + 1;
		return (free(res));
	}
	if (ft_strlen(res) >= 3 && res[0] == '$' && res[1] == '?' && res[2] != '\0')
		handle_general_utils(res, token);
	else
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
int	handle_all(t_token **token, char *str, int start, int i)
{
	if ((str[start] == '\"' && str[start + 1] == '\'') || (str[start] == '\''
			&& str[start + 1] == '\"'))
	{
		start = start + 1;
		handle_quote_state(token, str, &start, i - 1);
	}
	else
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (handle_quote(token, str, &start, i - 1))
				return (1);
		}
		else
			handle_general(token, str, &start, i);
	}
	return (0);
}
