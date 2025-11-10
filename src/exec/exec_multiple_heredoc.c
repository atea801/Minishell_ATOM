/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:52:23 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/10 14:47:36 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_heredoc_delims(char **delims)
{
	int	i;

	if (!delims)
		return ;
	i = 0;
	while (delims[i])
	{
		free(delims[i]);
		i++;
	}
	free(delims);
}

char	**extract_heredoc_delims(t_cmd *cmd)
{
	char	**delims;
	int		i;
	int		j;

	if (!cmd || cmd->count_heredocs == 0)
		return (NULL);
	delims = malloc(sizeof(char *) * (cmd->count_heredocs + 1));
	if (!delims)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd->argv[i])
	{
		if (ft_strcmp(cmd->argv[i], "<<") == 0 && cmd->argv[i + 1])
		{
			delims[j] = ft_strdup(cmd->argv[i + 1]);
			if (!delims[j])
				return (free_heredoc_delims(delims), free(delims), NULL);
			j++;
		}
		i++;
	}
	delims[j] = NULL;
	return (delims);
}

int	count_and_extract_heredocs(t_cmd *cmd)
{
	int	i;
	int	count;

	if (!cmd)
		return (0);
	while (cmd)
	{
		count = 0;
		if (cmd->heredoc_delim)
		{
			i = 0;
			while (cmd->heredoc_delim[i])
			{
				count++;
				i++;
			}
		}
		cmd->count_heredocs = count;
		cmd = cmd->next;
	}
	return (1);
}

int	multiple_heredoc_gestion(t_cmd *cmd, t_atom_env *env, int index)
{
	int		p_fd[2];
	pid_t	pid;
	char	*delimiter;

	if (g_signal_received == 2)
		return (1);
	if (!cmd || !cmd->heredoc_delim || !cmd->heredoc_delim[index])
		return (1);
	delimiter = cmd->heredoc_delim[index];
	if (pipe(p_fd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (close(p_fd[0]), close(p_fd[1]), perror("fork"), 1);
	if (pid == 0)
		handle_multi_heredoc_child(p_fd, delimiter, env);
	last_heredoc_checker(cmd, p_fd, index);
	if (multi_heredoc_signal_test(pid) == 1)
		return (1);
	return (0);
}

int	exec_multiple_heredoc(t_cmd *cmd, t_atom_env *env)
{
	int		heredoc_index;
	int		res;
	t_cmd	*current;

	setup_signals_heredoc_parent();
	current = cmd;
	while (current)
	{
		heredoc_index = 0;
		while (heredoc_index < current->count_heredocs)
		{
			res = multiple_heredoc_gestion(current, env, heredoc_index);
			if (res != 0)
			{
				g_signal_received = 0;
				setup_signals_prompt();
				return (1);
			}
			heredoc_index++;
		}
		current = current->next;
	}
	setup_signals_prompt();
	return (0);
}
