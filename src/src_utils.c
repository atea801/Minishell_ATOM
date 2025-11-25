/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:35:16 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 16:03:18 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_and_close_cmd(t_cmd *cmd_list)
{
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
}

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
		free_and_close_cmd(cmd_list);
		free(cmd_list);
		cmd_list = tmp;
	}
}
