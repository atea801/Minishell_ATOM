/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:36:57 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/15 16:47:30 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	token_2_to_cmd(t_token_2 **token_2, t_cmd **cmd)
{
	t_token_2	*t_head_2;
	t_cmd		*cmd_head;
	int			count;
	int			i;

	i = 0;
	t_head_2 = *token_2;
	cmd_head = *cmd;
	count = count_to_pipe(t_head_2);
	while (t_head_2 && t_head_2->type)
	{
		if (ft_strcmp(t_head_2->type, "PIPE") != 0)
		{
			fill_one_node(cmd_head, t_head_2, t_head_2->value, i);
			fill_out_in_file(cmd_head, t_head_2, t_head_2->value);
			set_heredoc_append(cmd_head, t_head_2);
			i++;
		}
		else if (ft_strcmp(t_head_2->type, "PIPE") == 0)
		{
			cmd_head = cmd_head->next;
			i = 0;
		}
		t_head_2 = t_head_2->next;
	}
}

void	fill_one_node(t_cmd *cmd_head, t_token_2 *t_head_2, char *str, int i)
{
	if (ft_strcmp(t_head_2->type, "CMD") == 0 || ft_strcmp(t_head_2->type,
			"ARGS") == 0)
	{
		cmd_head->argv[i] = ft_strdup(str);
		if (!cmd_head->argv[i])
			return ;
	}
	else
		return ;
}

void	fill_out_in_file(t_cmd *cmd_head, t_token_2 *t_head_2, char *str)
{
	if (ft_strcmp(t_head_2->type, "INFILE") == 0)
	{
		cmd_head->infile = ft_strdup(str);
		if (!cmd_head->infile)
			return ;
	}
	if (ft_strcmp(t_head_2->type, "OUTFILE") == 0)
	{
		cmd_head->outfile = ft_strdup(str);
		if (!cmd_head->outfile)
			return ;
	}
	else
		return ;
}

void	set_heredoc_append(t_cmd *cmd_head, t_token_2 *t_head_2)
{
	if (ft_strcmp(t_head_2->type, "APPEND") == 0)
		cmd_head->append = 1;
	if (ft_strcmp(t_head_2->type, "HEREDOC") == 0)
		cmd_head->here_doc = 1;
	else
		return ;
}

int	count_to_pipe(t_token_2 *t_head_2)
{
	int	count;

	count = 0;
	while (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type, "PIPE") != 0)
	{
		if (ft_strcmp(t_head_2->type, "CMD") == 0 || ft_strcmp(t_head_2->type,
				"ARGS") == 0)
			count++;
		t_head_2 = t_head_2->next;
	}
	return (count);
}
