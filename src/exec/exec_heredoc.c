
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
	ft_putstr_fd(line, pipe_fd[1]);
	ft_putchar_fd('\n', pipe_fd[1]);
	free(line);
}

int	process_heredocs(t_cmd *cmd, t_minishell *shell)
{
	int	result;

	result = exec_multiple_heredoc(cmd, shell);
	if (result != 0)
	{
		shell->exit_code = 130;
		return (1);
	}
	return (0);
}

void	secure_fd_in_after_heredoc(t_cmd *cmd, int index)
{
	if (index == cmd->count_heredocs - 1 && cmd->fd_in != -1)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
}
