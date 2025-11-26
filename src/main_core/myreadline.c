/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myreadline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:36:01 by aautret           #+#    #+#             */
/*   Updated: 2025/11/26 11:02:04 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_all_buffers(t_minishell *shell)
{
	if (shell->cmd)
	{
		free_cmd_list(shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->tok1)
	{
		free_token_1_only(shell->tok1);
		shell->tok1 = NULL;
	}
	if (shell->tok2)
	{
		free_token_2_list(&shell->tok2);
		shell->tok2 = NULL;
	}
	shell->tok1 = NULL;
	shell->tok2 = NULL;
	shell->should_execute = false;
	shell->buffers.prompt = NULL;
	shell->buffers.input = NULL;
}

void	my_readline(int ac, char **argv, t_minishell *shell)
{
	(void)ac;
	(void)argv;
	while (1)
	{
		free_all_buffers(shell);
		prepare_prompt_and_input(shell);
		if (handle_exit(shell))
			break ;
		if (handle_parsing_and_errors(shell))
			continue ;
		execute_commands_if_ready(shell);
		if (handle_exit(shell))
			break ;
		add_input_to_history(shell);
	}
}
