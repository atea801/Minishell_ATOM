/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:32:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 14:23:26 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	execute_child(t_minishell *shell, t_cmd *cmd, char **env)
{
	char	*path;

	handle_redirections(cmd);
	if (is_builtin(cmd->argv[0]))
	{
		shell->exit_code = execute_builtin(cmd);
		exit(shell->exit_code);
	}
	path = find_command_path(cmd->argv[0], shell);
	if (!path)
	{
		ft_putstr_fd("atom: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		exit(127);
	}
	execve(path, cmd->argv, env);
	perror("execve");
	free(path);
	exit(126);
}

static void	wait_all_childrens(pid_t *pids, int num_cmds, t_minishell *shell)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_cmds - 1)
		{
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	execute_multipipe(t_minishell *shell, t_cmd *cmd, char **env)
{
	int		num_cmd;
	int		**pipes;
	pid_t	*pids;
	t_cmd	*current;
	int		i;

	num_cmd = count_commands(cmd);
	pipes = create_pipes(num_cmd - 1);
	if (!pipes)
		return ;
	pids = malloc(sizeof(pid_t) * num_cmd);
	if (!pids)
	{
		close_all_pipes(pipes, num_cmd - 1);
		free_pipes(pipes, num_cmd - 1);
		return ;
	}
	current = cmd;
	i = 0;
	while (i < num_cmd)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			close_all_pipes(pipes, num_cmd - 1);
			wait_all_childrens(pids, i, shell);
			free_pipes(pipes, num_cmd - 1);
			free(pids);
			return ;
		}
		if (pids[i] == 0)
		{
			setup_pipe_redirections(pipes, i, num_cmd);
			execute_child(shell, current, env);
		}
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, num_cmd - 1);
	wait_all_childrens(pids, num_cmd, shell);
	free_pipes(pipes, num_cmd - 1);
	free(pids);
}
