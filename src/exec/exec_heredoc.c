
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
		setup_signals_heredoc();
		while (1)
		{
			line = readline("> ");
			if (g_signal_received == 2)
			{
				if (line)
					free(line);
				close(pipe_fd[1]);
				g_signal_received = 0;
				break ;
			}
			if (!line)
			{
				ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `",
					2);
				ft_putstr_fd(cmd->heredoc_delim[0], 2);
				ft_putendl_fd("')", 2);
				break ;
			}
			if (cmd->heredoc_delim && cmd->heredoc_delim[0]
				&& ft_strcmp(cmd->heredoc_delim[0], line) == 0)
			{
				free(line);
				break ;
			}
			write_here_doc(line, pipe_fd, env);
		}
		setup_signals_prompt();
		close(pipe_fd[1]);
		exit(0);
	}
	exit(1);
}

void	here_doc_infile(t_cmd *cmd, t_atom_env *env)
{
	int		p_fd[2];
	pid_t	pid;
	int		status;

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
		waitpid(pid, &status, 0);
		if (g_signal_received == 2)
		{
			close(p_fd[0]);
			g_signal_received = 0;
			return ;
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(p_fd[0]);
			g_signal_received = 0;
			return ;
		}
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
