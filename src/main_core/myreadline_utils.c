/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myreadline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:32:10 by aautret           #+#    #+#             */
/*   Updated: 2025/11/26 11:02:18 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	prepare_prompt_and_input(t_minishell *shell)
{
	shell->buffers.prompt = get_dynamic_prompt();
	if (isatty(STDIN_FILENO))
		shell->buffers.input = readline(shell->buffers.prompt);
}

static void	handle_exit_util(t_minishell *shell)
{
	if (shell->buffers.input)
		free(shell->buffers.input);
	if (shell->buffers.res)
		free(shell->buffers.res);
	if (shell->buffers.prompt)
		free(shell->buffers.prompt);
}

int	handle_exit(t_minishell *shell)
{
	if (!shell->buffers.input || ft_strcmp(shell->buffers.input, "exit") == 0)
	{
		if (shell->buffers.input)
			free(shell->buffers.input);
		if (shell->buffers.prompt)
			free(shell->buffers.prompt);
		printf("exit\n");
		if (shell->cmd)
		{
			free_cmd_list(shell->cmd);
			shell->cmd = NULL;
		}
		return (1);
	}
	if (shell->should_exit)
	{
		handle_exit_util(shell);
		if (shell->cmd)
		{
			free_cmd_list(shell->cmd);
			shell->cmd = NULL;
		}
		return (1);
	}
	return (0);
}

int	handle_parsing_and_errors(t_minishell *shell)
{
	shell->buffers.res = parsing_1(shell, shell->buffers.input);
	if (!shell->buffers.res)
	{
		if (shell->buffers.input)
			free(shell->buffers.input);
		if (shell->buffers.prompt)
			free(shell->buffers.prompt);
		return (1);
	}
	if (g_signal_received == 1)
		shell->exit_code = 130;
	return (0);
}

void	add_input_to_history(t_minishell *shell)
{
	if (isatty(STDIN_FILENO) && shell->buffers.input && *shell->buffers.input)
		add_history(shell->buffers.input);
	if (shell->buffers.input)
		free(shell->buffers.input);
	if (shell->buffers.res)
		free(shell->buffers.res);
	if (shell->buffers.prompt)
		free(shell->buffers.prompt);
}
