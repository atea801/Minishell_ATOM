/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:32:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/21 11:41:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	close_unused_fds(t_cmd *cmd_list, t_cmd *current_cmd)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp != current_cmd)
		{
			if (tmp->fd_in > 2)
			{
				close(tmp->fd_in);
				tmp->fd_in = -1;
			}
			if (tmp->fd_out > 2)
			{
				close(tmp->fd_out);
				tmp->fd_out = -1;
			}
		}
		tmp = tmp->next;
	}
}

static void	execute_child(t_minishell *shell, t_cmd *cmd, t_cmd *cmd_list,
		int num_cmd)
{
	char	*path;
	char	**env;

	env = env_list_to_tab_new(shell->env);
	handle_redirections(cmd);
	close_unused_fds(cmd_list, cmd);
	if (!cmd->argv || !cmd->argv[0])
	{
		free_env_tab(env);
		free_all_life(shell);
		free_pipes(shell->buffers.pipes, num_cmd - 1);
		exit(127);
	}
	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = execute_builtin(shell);
		free_env_tab(env);
		free_all_life(shell);
		free_pipes(shell->buffers.pipes, num_cmd - 1);
		exit(shell->exit_code);
	}
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_env_tab(env);
		free_all_life(shell);
		free_pipes(shell->buffers.pipes, num_cmd - 1);
		exit(127);
	}
	execve(path, cmd->argv, env);
	perror("execve");
	free(path);
	free_env_tab(env);
	free_all_life(shell);
	free_pipes(shell->buffers.pipes, num_cmd - 1);
	exit(126);
}

void	wait_all_childrens(pid_t *pids, int num_cmds, t_minishell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1)
			handle_child_status(shell, status);
		i++;
	}
}

static int	init_resources(int ***pipes, pid_t **pids, int num_cmd)
{
	*pipes = create_pipes(num_cmd - 1);
	if (!*pipes)
		return (0);
	*pids = malloc(sizeof(pid_t) * num_cmd);
	if (!*pids)
		return (check_pid_error(*pipes, num_cmd));
	return (1);
}

void	execute_multipipe(t_minishell *shell, t_cmd *cmd)
{
	int		num_cmd;
	pid_t	*pids;
	t_cmd	*current;
	int		i;

	num_cmd = count_commands(cmd);
	if (!init_resources(&shell->buffers.pipes, &pids, num_cmd))
		return ;
	current = cmd;
	i = -1;
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
			execute_child(shell, current, cmd, num_cmd);
		}
		current = current->next;
		if (pids[i] > 0 && shell->buffers.pipes && i >= 0 && i < num_cmd - 1
			&& shell->buffers.pipes[i])
		{
			if (shell->buffers.pipes[i][1] >= 0)
			{
				close(shell->buffers.pipes[i][1]);
				shell->buffers.pipes[i][1] = -1;
			}
		}
	}
	cleanup_on_error(pids, num_cmd, shell);
}
