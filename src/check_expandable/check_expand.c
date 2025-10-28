/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:27:38 by aautret           #+#    #+#             */
/*   Updated: 2025/10/28 15:25:42 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	in_single_quote(char *res, int pos)
{
	int	in_single;
	int	i;

	in_single = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == '\'')
			in_single = !in_single;
		i++;
	}
	return (in_single);
}

int	in_double_quote(char *res, int pos)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == '\"')
			in_double = !in_double;
		i++;
	}
	return (in_double);
}


void	check_expendable(char *res, t_token_2 *token_2)
{
	int		index;
	char	*pos;

	index = 0;
	while (token_2 && token_2->value)
	{
		if (res)
			pos = ft_strnstr(res + index, token_2->value, ft_strlen(res));
		if (pos && token_2->value[0] == '$')
		{
			index = pos - res;
			if ((!in_single_quote(res, index) && !in_double_quote(res, index))
				|| (in_double_quote(res, index) && !in_single_quote(res,
						index)))
				token_2->is_expand = 1;
			else if (in_single_quote(res, index))
				token_2->is_expand = 0;
			else
				token_2->is_expand = 0;
		}
		token_2 = token_2->next;
	}
}

