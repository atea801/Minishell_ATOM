/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:37 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/18 11:56:08 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_pid_error(int **pipes, int num_cmd)
{
	close_all_pipes(pipes, num_cmd - 1);
	free_pipes(pipes, num_cmd - 1);
	return (0);
}

int	cleanup_on_error(int **pipes, pid_t *pids, int num_cmd, t_minishell *shell)
{
	close_all_pipes(pipes, num_cmd - 1);
	wait_all_childrens(pids, num_cmd, shell);
	free_pipes(pipes, num_cmd - 1);
	free(pids);
	return (1);
}

void	multi_heredoc_readline(char *line, char *delimiter, int *p_fd,
		t_minishell *shell)
{
	while (1)
	{
		if (p_fd && p_fd[0] != -1)
		{
			close(p_fd[0]);
			p_fd[0] = -1;
		}
		line = readline("> ");
		if (g_signal_received == 2)
		{
			if (line)
				free(line);
			close_fds(shell->cmd);
			if (p_fd && p_fd[1] != -1)
			{
				close(p_fd[1]);
				p_fd[1] = -1;
			}
			exit(130);
		}
		else if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited ", 2);
			ft_putstr_fd("by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putendl_fd("')", 2);
			close_fds(shell->cmd);
			if (p_fd && p_fd[1] != -1)
			{
				close(p_fd[1]);
				p_fd[1] = -1;
			}
			break ;
		}
		if (ft_strcmp(delimiter, line) == 0)
		{
			close_fds(shell->cmd);
			free(line);
			if (p_fd && p_fd[1] != -1)
			{
				close(p_fd[1]);
				p_fd[1] = -1;
			}
			break ;
		}
		write_here_doc(line, p_fd, shell->env);
	}
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
