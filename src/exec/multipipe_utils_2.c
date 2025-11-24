/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:37 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/24 11:12:14 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_pid_error(int **pipes, int num_cmd)
{
	close_all_pipes(pipes, num_cmd - 1);
	free_pipes(pipes, num_cmd - 1);
	return (0);
}

void	close_all_cmd_fds(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (current->fd_in != -1)
		{
			close(current->fd_in);
			current->fd_in = -1;
		}
		if (current->fd_out != -1)
		{
			close(current->fd_out);
			current->fd_out = -1;
		}
		current = current->next;
	}
}

int	cleanup_on_error(pid_t *pids, int num_cmd, t_minishell *shell)
{
	close_all_pipes(shell->buffers.pipes, num_cmd - 1);
	close_all_cmd_fds(shell->cmd);
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
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
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
