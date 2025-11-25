/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:49:30 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/25 15:06:58 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_fork_error(t_minishell *shell, t_cmd *cmd)
{
	perror("fork");
	free(cmd->path);
	cmd->path = NULL;
	shell->exit_code = 1;
	return (0);
}

void	secure_exec(t_minishell *shell, char **tab_to_env)
{
	struct stat	path_stat;

	if (stat(shell->cmd->path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(shell->cmd->argv[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(shell->cmd->path);
		free_env_tab(tab_to_env);
		free_all_life(shell);
		exit(126);
	}
	execve(shell->cmd->path, shell->cmd->argv, tab_to_env);
	perror(shell->cmd->argv[0]);
	free(shell->cmd->path);
	free_env_tab(tab_to_env);
	free_all_life(shell);
	exit(127);
}

int	unfound_path(t_cmd *cmd, t_minishell *shell)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_code = 127;
	return (0);
}

int	init_cmd_path(t_cmd *cmd, t_minishell *shell)
{
	cmd->path = find_command_path(cmd->argv[0], shell);
	if (!cmd->path)
		if (!unfound_path(cmd, shell))
			return (0);
	return (1);
}

void	close_fds(t_cmd *cmd)
{
	if (cmd->fd_in != -1 && cmd->fd_in != 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1 && cmd->fd_out != 1)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}
