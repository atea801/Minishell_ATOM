/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 10:49:30 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/22 14:47:16 by tlorette         ###   ########.fr       */
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

void	secure_exec(t_cmd *cmd, char **tab_to_env)
{
	execve(cmd->path, cmd->argv, tab_to_env);
	perror(cmd->argv[0]);
	free(cmd->path);
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
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
}
