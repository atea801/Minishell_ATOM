/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:23:47 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/24 17:28:41 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	heredoc_signal_test(int *p_fd, pid_t pid, int *status)
{
	waitpid(pid, status, 0);
	if (g_signal_received == 2 || (WIFEXITED(*status)
			&& WEXITSTATUS(*status) == 130))
	{
		close(p_fd[0]);
		g_signal_received = 0;
		return ;
	}
}

char	*heredoc_readline(int **pipe_fd, t_cmd *cmd)
{
	char	*line;

	line = readline("> ");
	if (g_signal_received == 2)
	{
		if (line)
			free(line);
		if (pipe_fd && *pipe_fd && (*pipe_fd)[1] != -1)
			close((*pipe_fd)[1]);
		return (NULL);
	}
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited ", 2);
		ft_putstr_fd("by end-of-file (wanted `", 2);
		ft_putstr_fd(cmd->heredoc_delim[0], 2);
		ft_putendl_fd("')", 2);
		return (NULL);
	}
	if (cmd->heredoc_delim && cmd->heredoc_delim[0]
		&& ft_strcmp(cmd->heredoc_delim[0], line) == 0)
		return (free(line), NULL);
	printf("LINE = %s", line);
	return (line);
}

int	multi_heredoc_signal_test(pid_t pid, int *p_fd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (p_fd && p_fd[0] != -1)
	{
		close(p_fd[0]);
		p_fd[0] = -1;
	}
	if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
		|| (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		g_signal_received = 0;
		return (1);
	}
	g_signal_received = 0;
	return (0);
}

void	handle_multi_heredoc_child(int *p_fd, char *delimiter,
		t_minishell *shell)
{
	char	*line;

	setup_signals_heredoc();
	if (p_fd && p_fd[0] != -1)
		close(p_fd[0]);
	line = NULL;
	multi_heredoc_readline(line, delimiter, p_fd, shell);
	if (p_fd && p_fd[1] != -1)
		close(p_fd[1]);
	if (g_signal_received == 2)
	{
		free_all_life(shell);
		exit(130);
	}
	free_all_life(shell);
	exit(0);
}

void	exec_single_cmd_child(t_minishell *shell)
{
	char	**tab_to_env;

	restore_default_signals();
	handle_redirections(shell->cmd);
	tab_to_env = env_list_to_tab(shell->env);
	secure_exec(shell, tab_to_env);
	free_env_tab(tab_to_env);
}
