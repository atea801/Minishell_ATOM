/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:58:21 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/24 11:13:07 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	is_triple_redir(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		|| (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<'))
		return (1);
	return (0);
}

int	is_double_redir(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
		return (1);
	return (0);
}

int	handle_double_redir(char *input, char *res, int *i, int *j)
{
	res[(*j)++] = input[(*i)++];
	res[(*j)++] = input[(*i)++];
	if (input[*i] && input[*i] != ' ' && !is_redir(input[*i]))
		res[(*j)++] = ' ';
	return (1);
}

int	handle_single_redir(char *input, char *res, int *i, int *j)
{
	res[(*j)++] = input[(*i)++];
	if (input[*i] && input[*i] != ' ' && !is_redir(input[*i]))
		res[(*j)++] = ' ';
	return (1);
}

int	is_redir(char c)
{
	return (c == '>' || c == '<');
}
