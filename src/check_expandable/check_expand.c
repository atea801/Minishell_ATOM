/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:27:38 by aautret           #+#    #+#             */
/*   Updated: 2025/10/23 11:23:40 by aautret          ###   ########.fr       */
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
	// int		in_double;
	// int		in_single;
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
			// in_single = in_single_quote(res, index);
			// in_double = in_double_quote(res, index);
			// if ((!in_single && !in_double) || (in_double && !in_single))
			// 	token_2->is_expand = 1;
			// else
			// 	token_2->is_expand = 0;
			if (in_single_quote(res, index))
				token_2->is_expand = 0;
		}
		// printf("%s is_expand = %d\n", token_2->value, token_2->is_expand);
		token_2 = token_2->next;
	}
}
