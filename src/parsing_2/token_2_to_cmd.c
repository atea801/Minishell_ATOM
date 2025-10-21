/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:36:57 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/21 16:00:35 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	token_2_to_cmd(t_cmd **cmd, t_token_2 **token_2)
{
	t_token_2	*t_head_2;
	t_cmd		*current_cmd;
	t_cmd		*new_cmd;

	t_head_2 = *token_2;
	*cmd = NULL;
	while (t_head_2 && t_head_2->type)
	{
		if (init_cmd_struct(&new_cmd) != 0)
			return ;
		if (*cmd == NULL)
			*cmd = new_cmd;
		else
		{
			current_cmd = *cmd;
			while (current_cmd->next)
				current_cmd = current_cmd->next;
			current_cmd->next = new_cmd;
		}
		fill_cmd_until_pipe(new_cmd, &t_head_2);
		if (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type,
				"PIPE") == 0)
			t_head_2 = t_head_2->next;
	}
}

void	fill_cmd_until_pipe(t_cmd *cmd, t_token_2 **t_head_2)
{
	int	count;
	int	i;

	count = count_args_to_pipe(*t_head_2);
	cmd->argv = malloc(sizeof(char *) * (count + 1));
	if (!cmd->argv)
		return ;
	i = 0;
	while (*t_head_2 && (*t_head_2)->type && ft_strcmp((*t_head_2)->type,
			"PIPE") != 0)
	{
		if (ft_strcmp((*t_head_2)->type, "CMD") == 0
			|| ft_strcmp((*t_head_2)->type, "ARGS") == 0)
		{
			cmd->argv[i] = ft_strdup((*t_head_2)->value);
			if (!cmd->argv[i])
				return ;
			i++;
		}
		set_heredoc_delim_append(t_head_2, &cmd);
		set_infile_cmd(t_head_2, &cmd);
		*t_head_2 = (*t_head_2)->next;
	}
	cmd->argv[i] = NULL;
	cmd->argc = i;
}

int	count_args_to_pipe(t_token_2 *token_2)
{
	int			count;
	t_token_2	*t_head_2;

	count = 0;
	t_head_2 = token_2;
	while (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type, "PIPE") != 0)
	{
		if (ft_strcmp(t_head_2->type, "ARGS") == 0 || ft_strcmp(t_head_2->type,
				"CMD") == 0)
			count++;
		t_head_2 = t_head_2->next;
	}
	return (count);
}

void	print_cmd_list(t_cmd *cmd)
{
	int node = 0;
	int i;

	while (cmd)
	{
		printf("\nCOMMANDE %d\n", node);
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				printf("argv[%d] : %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		if (cmd->infile)
			printf("infile : %s\n", cmd->infile);
		if (cmd->outfile)
			printf("outfile : %s\n", cmd->outfile);
		printf("HEREDOC : %d\n", cmd->here_doc);
		printf("APPEND : %d\n", cmd->append);
		cmd = cmd->next;
		node++;
	}
}

void	set_heredoc_delim_append(t_token_2 **token_2, t_cmd **cmd)
{
	t_cmd		*cmd_head;
	t_token_2	*t_head_2;

	cmd_head = *cmd;
	t_head_2 = *token_2;
	while (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type, "PIPE") != 0)
	{
		if (ft_strcmp(t_head_2->type, "HEREDOC_DELIM") == 0)
		{
			cmd_head->heredoc_delim = ft_strdup(t_head_2->value);
			cmd_head->here_doc = 1;
		}
		if (ft_strcmp(t_head_2->type, "APPEND") == 0)
			cmd_head->append = 1;
		t_head_2 = t_head_2->next;
	}
}

void	set_infile_cmd(t_token_2 **token_2, t_cmd **cmd)
{
	t_cmd		*cmd_head;
	t_token_2	*t_head_2;

	cmd_head = *cmd;
	t_head_2 = *token_2;
	while (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type, "PIPE") != 0)
	{
		if (ft_strcmp(t_head_2->type, "INFILE") == 0)
		{
			cmd_head->infile = ft_strdup(t_head_2->value);
			cmd_head->here_doc = 0;
		}
		if (ft_strcmp(t_head_2->type, "OUTFILE") == 0)
		{
			cmd_head->outfile = ft_strdup(t_head_2->value);
			cmd_head->append = 0;
		}
		t_head_2 = t_head_2->next;
	}
}
