/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_find_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:36:06 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/06 18:56:54 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	fill_cmd_or_args(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;
	t_token_2	*prev;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	prev = NULL;
	if (!token_1)
		return ;
	if (t_head_1->type && t_head_1->next->value
		&& (ft_strcmp(t_head_1->type, "MOT") == 0))
	{
		if (prev)
			prev->next = t_head_2->next;
		if (!t_head_2->type)
		{
			t_head_2->type = "CMD";
			t_head_2->value = copy_token_value(t_head_1->value);
		}
		if (t_head_2 && prev && ft_strcmp(prev->type, "MOT"))
		{
			t_head_2->type = "ARGS";
			t_head_2->value = copy_token_value(t_head_1->next->value);
		}
	}
}

void	fill_redirin_redirout(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	if (!token_1)
		return ;
	if (t_head_1->type && (ft_strcmp(t_head_1->type, "REDIR_IN") == 0))
	{
		t_head_2->type = "INFILE";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
	else if (t_head_1->type && (ft_strcmp(t_head_1->type, "REDIR_OUT") == 0))
	{
		t_head_2->type = "OUTFILE";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
}
