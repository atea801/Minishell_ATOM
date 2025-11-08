/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:52:23 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/08 11:12:23 by tlorette         ###   ########.fr       */
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
		i = -1;
		while (cmd->argv && cmd->argv[++i])
		{
			if (ft_strcmp(cmd->argv[i], "<<") == 0)
				count++;
		}
		cmd->count_heredocs = count;
		if (count > 0)
			cmd->heredoc_delim = extract_heredoc_delims(cmd);
		else
			cmd->heredoc_delim = NULL;
		cmd = cmd->next;
	}
	return (1);
}

void	multiple_heredoc_gestion(t_cmd *cmd, t_atom_env *env, int index)
{
	int		p_fd[2];
	pid_t	pid;
	char	*delimiter;
	char	*line;

	if (!cmd || !cmd->heredoc_delim || !cmd->heredoc_delim[index])
		return ;
	delimiter = cmd->heredoc_delim[index];
	if (pipe(p_fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (close(p_fd[0]), close(p_fd[1]), perror("fork"));
	if (pid == 0)
	{
		line = NULL;
		multi_heredoc_readline(line, delimiter, p_fd, env);
		exit(0);
	}
	else
	{
		last_heredoc_checker(cmd, p_fd, index);
		wait(NULL);
	}
}

void	exec_multiple_heredoc(t_cmd *cmd, t_atom_env *env)
{
	int	heredoc_index;

	while (cmd)
	{
		heredoc_index = 0;
		while (heredoc_index < cmd->count_heredocs)
		{
			multiple_heredoc_gestion(cmd, env, heredoc_index);
			heredoc_index++;
		}
		cmd = cmd->next;
	}
}


