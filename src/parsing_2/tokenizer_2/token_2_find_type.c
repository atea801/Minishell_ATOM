/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_find_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:36:06 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 16:15:50 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Remplie le contenu du token_2, type == CMD et rempli la value
 *
 * @param token_1
 * @param token_2
 */
void	fill_cmd(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	t_head_2->type = "CMD";
	if (ft_strnstr(t_head_1->value, "__SINGLE_QUOTE__",
			ft_strlen(t_head_1->value)))
	{
		t_head_2->is_expand = 0;
		t_head_2->value = copy_token_value(t_head_1->value + 16);
	}
	else
	{
		t_head_2->value = copy_token_value(t_head_1->value);
	}
}

/**
 * @brief Remplie le contenu du token_2, type == ARGS et rempli la value
 *
 * @param token_1
 * @param token_2
 */
void	fill_args(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	t_head_2->type = "ARGS";
	if (ft_strnstr(t_head_1->value, "__SINGLE_QUOTE__",
			ft_strlen(t_head_1->value)))
	{
		t_head_2->is_expand = 0;
		t_head_2->value = copy_token_value(t_head_1->value + 16);
	}
	else
	{
		t_head_2->value = copy_token_value(t_head_1->value);
	}
}

/**
 * @brief Reassigne le type APPEND et HEREDOC de token_1 a token_2
 *
 * @param token_1
 * @param token_2
 */
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

/**
 * @brief Reassigne le type REDIR_IN / REDIR_OUT / PIPE de token_1 a token_2
 *
 * @param token_1
 * @param token_2
 */
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

void	fill_expand(t_token **token_1, t_token_2 **token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = *token_1;
	t_head_2 = *token_2;
	if (!token_1)
		return ;
	if (t_head_1->value && (ft_strcmp(t_head_1->value, "$?") == 0))
	{
		t_head_2->type = "ARGS";
		t_head_2->value = copy_token_value(t_head_1->value);
	}
}
