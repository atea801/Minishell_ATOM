/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:34:00 by aautret           #+#    #+#             */
/*   Updated: 2025/11/27 17:11:32 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	res_to_tokenizer1(t_minishell *shell)
{
	if (shell->buffers.res)
	{
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
		init_token_struct(&shell->tok1, &shell->tok2);
		tokenizer(shell->tok1, shell->buffers.res);
		set_token_error(&shell->tok1);
	}
}

static void	prepare_command_data(t_minishell *shell)
{
	check_expendable(shell->buffers.res, shell->tok2);
	expand_all_tokens(shell, shell->tok2);
	token_2_to_cmd(&shell->cmd, &shell->tok2);
}

void	execute_commands_if_ready(t_minishell *shell)
{
	int	parsing_res;

	res_to_tokenizer1(shell);
	parsing_res = parsing_2(shell, shell->tok1, shell->tok2);
	if (parsing_res == 0)
	{
		shell->should_execute = true;
		prepare_command_data(shell);
	}
	if (shell->should_execute && shell->cmd)
	{
		count_and_extract_heredocs(shell->cmd);
		if (process_heredocs(shell->cmd, shell) == 0)
		{
			if (shell->cmd->next && has_real_command(shell->cmd))
				execute_multipipe(shell, shell->cmd);
			else if (has_real_command(shell->cmd))
				exec_single_cmd(shell);
		}
		close_all_cmd_fds(shell->cmd);
	}
	if (isatty(STDIN_FILENO))
		setup_signals_prompt();
}
