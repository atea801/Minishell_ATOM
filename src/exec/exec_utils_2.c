/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:50:49 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 14:20:28 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	free_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	setup_pipe_redirections(int **pipes, int cmd_index, int num_cmds)
{
	if (cmd_index > 0)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < num_cmds - 1)
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_all_pipes(pipes, num_cmds - 1);
}
