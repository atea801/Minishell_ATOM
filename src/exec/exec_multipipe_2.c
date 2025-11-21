/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipe_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:00:58 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/21 12:38:12 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	execute_child(t_minishell *shell, t_cmd *cmd, t_cmd *cmd_list,
		int num_cmd)
{
	char	*path;
	char	**env;

	env = env_list_to_tab_new(shell->env);
	handle_redirections(cmd);
	close_unused_fds(cmd_list, cmd);
	if (!cmd->argv || !cmd->argv[0])
	{
		free_pipes_env_and_all(shell, env, num_cmd);
		exit(127);
	}
	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = execute_builtin(shell);
		free_pipes_env_and_all(shell, env, num_cmd);
		exit(shell->exit_code);
	}
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
		no_command_in_child(shell, cmd, env, num_cmd);
	execve(path, cmd->argv, env);
	perror("execve");
	free(path);
	free_pipes_env_and_all(shell, env, num_cmd);
	exit(126);
}

static void	clean_child_exec(t_minishell *shell, int num_cmd, pid_t *pids)
{
	t_cmd	*current;
	int		i;

	i = -1;
	current = shell->cmd;
	while (++i < num_cmd && current)
	{
		pids[i] = fork();
		if (pids[i] == -1 && cleanup_on_error(pids, i, shell))
			return ;
		if (pids[i] == 0)
		{
			restore_default_signals();
			setup_pipe_redirections(shell->buffers.pipes, i, num_cmd, current);
			close_all_pipes(shell->buffers.pipes, num_cmd - 1);
			free(pids);
			execute_child(shell, current, shell->cmd, num_cmd);
		}
		current = current->next;
	}
}

void	execute_multipipe(t_minishell *shell)
{
	int		num_cmd;
	pid_t	*pids;
	t_cmd	*current;
	int		i;

	num_cmd = count_commands(shell->cmd);
	if (!init_resources(&shell->buffers.pipes, &pids, num_cmd))
		return ;
	current = shell->cmd;
	clean_child_exec(shell, num_cmd, pids);
	i = num_cmd - 2;
	if (pids[i] > 0 && shell->buffers.pipes && i >= 0 && i < num_cmd - 1
		&& shell->buffers.pipes[i])
	{
		if (shell->buffers.pipes[i][1] >= 0)
		{
			close(shell->buffers.pipes[i][1]);
			shell->buffers.pipes[i][1] = -1;
		}
	}
	cleanup_on_error(pids, num_cmd, shell);
}
