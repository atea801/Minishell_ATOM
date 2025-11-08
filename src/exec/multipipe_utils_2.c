/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:37 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/08 11:01:59 by tlorette         ###   ########.fr       */
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
		t_atom_env *env)
{
	close(p_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break ;
		}
		write_here_doc(line, p_fd, env);
	}
	close(p_fd[1]);
}

void	last_heredoc_checker(t_cmd *cmd, int *p_fd, int index)
{
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
