/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:44:26 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:02 by tlorette         ###   ########.fr       */
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
	if (cmd->infile)
		redirect_input(cmd->infile);
	if (cmd->outfile)
	{
		if (cmd->append == 1)
			redirect_append(cmd->outfile);
		else
			redirect_output(cmd->outfile);
	}
}

void	exec_single_cmd(t_minishell *shell, t_cmd *cmd, char **tab_to_env)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	// if (is_builtin(cmd->argv[0]) == 1)
	// {
	// 	shell->exit_code = execute_builtin(shell, cmd);
	// 	return ;
	// }
	cmd->path = find_command_path(cmd->argv[0], shell);
	if (!cmd->path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd->path);
		cmd->path = NULL;
		shell->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		handle_redirections(cmd);
		execve(cmd->path, cmd->argv, tab_to_env);
		perror(cmd->argv[0]);
		free(cmd->path);
		exit(127);
	}
	free(cmd->path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_code = 128 + WTERMSIG(status);
}
