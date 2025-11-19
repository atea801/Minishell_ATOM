/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:44:26 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/19 11:43:37 by aautret          ###   ########.fr       */
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

void	exec_single_cmd(t_minishell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**tab_to_env;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	tab_to_env = NULL;
	// tab_to_env = env_list_to_tab(shell->env);
	if (is_builtin(cmd->argv[0]) == 1)
	{
		shell->exit_code = execute_builtin(shell);
		return ;
	}
	if (!init_cmd_path(cmd, shell))
		return ;
	pid = fork();
	if (pid == -1)
		if (!check_fork_error(shell, cmd))
			return ;
	if (pid == 0)
	{
		restore_default_signals();
		tab_to_env = env_list_to_tab(shell->env);
		secure_exec(cmd, tab_to_env);
	}
	close_fds(cmd);
	free(cmd->path);
	free_env_tab(tab_to_env);
	waitpid(pid, &status, 0);
	handle_child_status(shell, status);
}
