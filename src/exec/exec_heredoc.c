
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:14:40 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/07 10:18:08 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	exec_heredoc(t_cmd *cmd, int *pipe_fd, t_atom_env *env)
{
	char	*line;

	if (cmd->here_doc == 1)
	{
		close(pipe_fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (cmd->heredoc_delim && cmd->heredoc_delim[0]
				&& ft_strcmp(cmd->heredoc_delim[0], line) == 0)
			{
				free(line);
				break ;
			}
			write_here_doc(line, pipe_fd, env);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	exit(1);
}

void	here_doc_infile(t_cmd *cmd, t_atom_env *env)
{
	int		p_fd[2];
	pid_t	pid;

	if (!cmd)
		return ;
	if (pipe(p_fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (close(p_fd[0]), close(p_fd[1]), perror("fork"));
	if (pid == 0)
		exec_heredoc(cmd, p_fd, env);
	else
	{
		close(p_fd[1]);
		wait(NULL);
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		cmd->fd_in = p_fd[0];
	}
}

void	write_here_doc(char *line, int *pipe_fd, t_atom_env *env)
{
	char	*expanded;
	char	*var_value;

	if (line[0] == '$' && line[1] != '\0')
	{
		var_value = search_in_list(&env, line);
		if (var_value)
			expanded = ft_strdup(var_value);
		else
			expanded = ft_strdup("");
		free(line);
		line = expanded;
	}
	printf("%s\n", line);
	ft_putstr_fd(line, pipe_fd[1]);
	ft_putchar_fd('\n', pipe_fd[1]);
	free(line);
}
