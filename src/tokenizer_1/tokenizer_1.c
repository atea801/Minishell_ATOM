/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:39:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/17 17:55:11 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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
		if (str[i] == '\"' || str[i] == '\'')
		{
			start = i;
			i = skip_quote(str, i);
		}
		if (str[i + 1] == ' ' || str[i + 1] == 0 || str[i + 1] == '\"' || str[i + 1] == '\'')
		{
			handle_all(&token, str, start, i);
			start = i + 1;
			while (str[start] && str[start] == ' ')
			start++;
		}
	}
}
