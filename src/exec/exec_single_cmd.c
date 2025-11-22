/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:44:26 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/22 17:08:14 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	exec_single_cmd(t_minishell *shell)
{
	pid_t	pid;
	int		status;

	if (!shell->cmd || !shell->cmd->argv || !shell->cmd->argv[0]
		|| !shell->cmd->argv[0][0])
	{
		shell->exit_code = 0;
		return ;
	}
	if (shell->cmd->has_redir_error)
		return (shell->exit_code = 1, close_fds(shell->cmd));
	if (is_builtin(shell->cmd->argv[0]) == 1)
		return (shell->exit_code = execute_builtin(shell),
			close_fds(shell->cmd));
	if (!init_cmd_path(shell->cmd, shell))
		return (close_fds(shell->cmd));
	pid = fork();
	if (pid == -1)
		return (check_fork_error(shell, shell->cmd), close_fds(shell->cmd));
	if (pid == 0)
		exec_single_cmd_child(shell);
	close_fds(shell->cmd);
	free(shell->cmd->path);
	waitpid(pid, &status, 0);
	handle_child_status(shell, status);
}

