/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:35:16 by aautret           #+#    #+#             */
/*   Updated: 2025/10/09 10:48:34 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_all(t_token *token_head, t_atom_env *env_head, t_token_2 *token_2)
{
	if (token_head)
		free_token_list(token_head, token_2);
	if (env_head)
		free_env_list(env_head);
	// if (cmd_list)
	// 	free_cmd_list(cmd_list);
	// if (tab_env)
	// 	free_env_tab(tab_env);
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

	if (!cmd_list)
		return ;
	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->cmd)
			free(cmd_list->cmd);
		if (cmd_list->args)
			free(cmd_list->args);
		if (cmd_list->infile)
			free(cmd_list->infile);
		if (cmd_list->outfile)
			free(cmd_list->outfile);
		if (cmd_list->append)
			free(cmd_list->append);
		if (cmd_list->here_doc)
			free(cmd_list->here_doc);
		free(cmd_list);
		cmd_list = tmp;
	}
}

void	free_env_tab(char **tab_env)
{
	int	i;

	i = 0;
	if (!tab_env)
		return ;
	while (tab_env[i])
	{
		free(tab_env[i]);
		i++;
	}
	free(tab_env);
}
