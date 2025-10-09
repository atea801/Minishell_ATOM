/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/09 16:41:29 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_error(t_token *token_head)
{
	t_token	*t_head_1;

	t_head_1 = token_head;
	while (t_head_1)
	{
		if (ft_strcmp(t_head_1->type, "ERROR") == 0)
			return (1);
		t_head_1 = t_head_1->next;
	}
	return (0);
}

int	parsing_2(t_token *token_head, t_token_2 *token_2)
{
	t_token_2	*t_head_2;
	t_token		*t_head_1;

	t_head_1 = token_head;
	t_head_2 = token_2;
	if (check_error(t_head_1) > 0)
		return (1);
	tokenizer_2(t_head_1, t_head_2);
	if (check_all(&t_head_2) > 0)
		return (1);
	return (0);
}

int	in_single_quote(char *res, int pos)
{
	int	in_single;
	int	i;

	in_single = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == 39)
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
		if (res[i] == 34)
			in_double = !in_double;
		i++;
	}
	return (in_double);
}

void	check_expendable(char *res, t_token_2 *token_2)
{
	int		in_double;
	int		in_single;
	int		index;
	char	*pos;

	while (token_2 && token_2->value)
	{
		pos = ft_strnstr(res, token_2->value, ft_strlen(res));
		if (pos && token_2->value[0] == '$')
		{
			index = pos - res;
			in_single = in_single_quote(res, index);
			in_double = in_double_quote(res, index);
			if ((!in_single && !in_double) || (in_double && !in_single))
				token_2->is_expand = 1;
			else
				token_2->is_expand = 0;
		}
		else
			token_2->is_expand = 0;
		printf("is_expand = %d\n", token_2->is_expand);
		token_2 = token_2->next;
	}
}
