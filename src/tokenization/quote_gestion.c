/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:35:21 by aautret           #+#    #+#             */
/*   Updated: 2025/09/26 14:28:51 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	quote_state(char c, char next)
{
	if ((c == '"' && next == 39) || (c == 39 && next == '"'))
		return (1);
	return (0);
}

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

void	handle_quote_state(t_token **token, char *str, int *start, int end)
{
	char	*res;

	res = malloc_token(end, *start);
	copy_word(res, str, end, *start);
	put_token(token, res);
}

void	handle_quote(t_token **token, char *str, int *start, int end)
{
	char	*res;

	res = malloc_token(end, *start + 1);
	copy_word(res, str, end, *start + 1);
	put_token(token, res);
	(*start) += 1;
}

void	handle_general(t_token **token, char *str, int *start, int end)
{
	char	*res;

	res = malloc_token(end, *start);
	copy_word(res, str, end, *start);
	put_token(token, res);
	(*start) = end + 2;
}

void	handle_all(t_token **token, char *str, int *start, int i)
{
	if (str[i] == '"' || str[i] == 39)
		handle_quote(token, str, start, i - 1);
	else
		handle_general(token, str, start, i);
}
