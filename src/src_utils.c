/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:35:16 by aautret           #+#    #+#             */
/*   Updated: 2025/11/21 12:39:28 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_token_list(t_token *head, t_token_2 *head_2)
{
	t_token		*tmp;
	t_token_2	*tmp_2;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
	if (!head_2)
		return ;
	while (head_2)
	{
		tmp_2 = head_2->next;
		if (head_2->value)
			free(head_2->value);
		free(head_2);
		head_2 = tmp_2;
	}
}

void	free_env_list(t_atom_env *head)
{
	t_atom_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		if (head->key)
			free(head->key);
		free(head);
		head = tmp;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;
	int		i;

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->argv)
		{
			i = -1;
			while (cmd_list->argv[++i])
				free(cmd_list->argv[i]);
			free(cmd_list->argv);
		}
		if (cmd_list->infile)
			free(cmd_list->infile);
		if (cmd_list->outfile)
			free(cmd_list->outfile);
		if (cmd_list->heredoc_delim)
			free_heredoc_delims(cmd_list->heredoc_delim);
		if (cmd_list->fd_in != -1)
			close(cmd_list->fd_in);
		if (cmd_list->fd_out != -1)
			close(cmd_list->fd_out);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	free_env_tab(char **tab_env)
{
	int	i;

	if (!tab_env)
		return ;
	i = 0;
	while (tab_env[i])
	{
		free(tab_env[i]);
		i++;
	}
	free(tab_env);
}

void	free_all_life(t_minishell *shell)
{
	free_env_list(shell->env);
	free_cmd_list(shell->cmd);
	free_token_1_only(shell->tok1);
	free_token_2_list(&shell->tok2);
	if (shell->buffers.prompt)
		free(shell->buffers.prompt);
	if (shell->buffers.input)
		free(shell->buffers.input);
	if (shell->buffers.res)
		free(shell->buffers.res);
}
