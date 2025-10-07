/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_find_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:36:06 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/07 15:39:21 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"


void	fill_cmd(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	// if (!token_1)
	// 	return ;
	t_head_2->type = "CMD";
	t_head_2->value = copy_token_value(t_head_1->value);
}

void	fill_args(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	t_head_2->type = "ARGS";
	t_head_2->value = copy_token_value(t_head_1->value);
}

void	fill_heredoc_append(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	if (!token_1)
		return ;
	if (t_head_1->type && (ft_strcmp(t_head_1->type, "APPEND") == 0))
	{
		t_head_2->type = "APPEND";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
	else if (t_head_1->type && (ft_strcmp(t_head_1->type, "HEREDOC") == 0))
	{
		t_head_2->type = "HEREDOC";
		t_head_2->value = copy_token_value(t_head_1->value);
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
		t_head_2->type = "REDIR_IN";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
	else if (t_head_1->type && (ft_strcmp(t_head_1->type, "REDIR_OUT") == 0))
	{
		t_head_2->type = "REDIR_OUT";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
	else if (t_head_1->type && (ft_strcmp(t_head_1->type, "PIPE") == 0))
	{
		t_head_2->type = "PIPE";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
}
