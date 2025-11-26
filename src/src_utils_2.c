/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:48:02 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/26 18:02:51 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_token_1_only(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		free(head);
		head = tmp;
	}
}

void	free_token_2_list(t_token_2 **t_head_2)
{
	t_token_2	*head_2;
	t_token_2	*tmp_2;

	if (!t_head_2 || !*t_head_2)
		return ;
	head_2 = *t_head_2;
	while (head_2)
	{
		tmp_2 = head_2->next;
		if (head_2->value)
			free(head_2->value);
		free(head_2);
		head_2 = tmp_2;
	}
	*t_head_2 = NULL;
}

void	free_all_life(t_minishell *shell)
{
	if (shell->cmd)
		close_all_cmd_fds(shell->cmd);
	free_env_list(shell->env);
	if (shell->cmd)
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
