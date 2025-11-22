/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:37 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/21 17:48:39 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_pid_error(int **pipes, int num_cmd)
{
	close_all_pipes(pipes, num_cmd - 1);
	free_pipes(pipes, num_cmd - 1);
	return (0);
}

int	cleanup_on_error(pid_t *pids, int num_cmd, t_minishell *shell)
{
	close_all_pipes(shell->buffers.pipes, num_cmd - 1);
	wait_all_childrens(pids, num_cmd, shell);
	free_pipes(shell->buffers.pipes, num_cmd - 1);
	free(pids);
	return (1);
}

void	multi_heredoc_readline(char *line, char *delimiter, int *p_fd,
		t_minishell *shell)
{
	while (1)
	{
		line = readline("> ");
		if (g_signal_received == 2)
		{
			free_and_close_before_ctrlc(shell, line, p_fd);
			exit(130);
		}
		else if (!line)
		{
			write_ctrld_error_msg(shell, delimiter, p_fd);
			break ;
		}
		if (ft_strcmp(delimiter, line) == 0)
		{
			free_and_close_before_delim(shell, line, p_fd);
			break ;
		}
		write_here_doc(line, p_fd, shell->env);
	}
	close(p_fd[1]);
}

void	last_heredoc_checker(t_cmd *cmd, int *p_fd, int index)
{
	if (!cmd)
	{
		if (p_fd && p_fd[0] != -1)
			close(p_fd[0]);
		return ;
	}
	close(p_fd[1]);
	if (index == cmd->count_heredocs - 1)
	{
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		cmd->fd_in = p_fd[0];
	}
	else
		close(p_fd[0]);
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
