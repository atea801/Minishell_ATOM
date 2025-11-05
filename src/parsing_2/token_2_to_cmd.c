/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_to_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:58:02 by aautret           #+#    #+#             */
/*   Updated: 2025/11/04 14:19:41 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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

static int	allocate_argv(t_cmd *cmd, t_token_2 *t_head_2)
{
	int	count;

	count = count_args_to_pipe(t_head_2);
	cmd->argv = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->argv)
		return (-1);
	return (0);
}

static int	add_cmd_arg(t_cmd *cmd, t_token_2 *token, int index)
{
	if (ft_strcmp(token->type, "CMD") == 0 || ft_strcmp(token->type,
			"ARGS") == 0)
	{
		if (cmd->argv[index])
			free(cmd->argv[index]);
		cmd->argv[index] = ft_strdup(token->value);
		if (!cmd->argv[index])
			return (-1);
		return (1);
	}
	return (0);
}

static void	process_current_redirection(t_cmd *cmd, t_token_2 *token)
{
	if (ft_strcmp(token->type, "HEREDOC_DELIM") == 0)
	{
		if (cmd->heredoc_delim)
			free(cmd->heredoc_delim);
		cmd->heredoc_delim = ft_strdup(token->value);
		cmd->here_doc = 1;
	}
	else if (ft_strcmp(token->type, "APPEND") == 0)
		cmd->append = 1;
	else if (ft_strcmp(token->type, "INFILE") == 0)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(token->value);
		cmd->here_doc = 0;
	}
	else if (ft_strcmp(token->type, "OUTFILE") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(token->value);
		cmd->append = 0;
	}
}

void	fill_cmd_until_pipe(t_cmd *cmd, t_token_2 **t_head_2)
{
	int	i;
	int	result;

	if (allocate_argv(cmd, *t_head_2) == -1)
		return ;
	i = 0;
	while (*t_head_2 && (*t_head_2)->type && ft_strcmp((*t_head_2)->type,
			"PIPE") != 0)
	{
		result = add_cmd_arg(cmd, *t_head_2, i);
		if (result == -1)
			return ;
		i += result;
		process_current_redirection(cmd, *t_head_2);
		*t_head_2 = (*t_head_2)->next;
	}
	cmd->argv[i] = NULL;
	cmd->argc = i;
}

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
