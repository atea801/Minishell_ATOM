/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:41:38 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/27 17:08:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	close_all_buffer_pipes(t_minishell *shell, pid_t *pids, int num_cmd,
		int i)
{
	if (pids[i] > 0 && shell->buffers.pipes && i >= 0 && i < num_cmd - 1
		&& shell->buffers.pipes[i])
	{
		if (shell->buffers.pipes[i][1] >= 0)
		{
			close(shell->buffers.pipes[i][1]);
			shell->buffers.pipes[i][1] = -1;
		}
	}
}

void	inside_child_security(t_minishell *shell, t_cmd *current, int num_cmd,
		int i)
{
	restore_default_signals();
	setup_pipe_redirections(shell->buffers.pipes, i, num_cmd, current);
	close_all_pipes(shell->buffers.pipes, num_cmd - 1);
}

void	handle_child_status(t_minishell *shell, int status)
{
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit (core dumped)\n", 19);
			shell->exit_code = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			shell->exit_code = 130;
		}
		else
			shell->exit_code = 128 + WTERMSIG(status);
	}
}

void	execute_child_and_close(t_minishell *shell, t_cmd *cmd,
		t_cmd *current, int num_cmd)
{
	close_unused_fds(cmd, current);
	execute_child(shell, current, num_cmd, cmd);
}
