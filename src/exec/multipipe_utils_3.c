/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:20:42 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/21 13:06:42 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	write_ctrld_error_msg(t_minishell *shell, char *delimiter, int *p_fd)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
	if (p_fd && p_fd[0])
	{
		close(p_fd[0]);
		p_fd[0] = -1;
	}
	close_fds(shell->cmd);
}

void	free_and_close_before_ctrlc(t_minishell *shell, char *line, int *p_fd)
{
	if (line)
		free(line);
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
	if (p_fd && p_fd[0])
	{
		close(p_fd[0]);
		p_fd[0] = -1;
	}
	close_fds(shell->cmd);
	free_all_life(shell);
}

void	free_and_close_before_delim(t_minishell *shell, char *line, int *p_fd)
{
	free(line);
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
	if (p_fd && p_fd[0])
	{
		close(p_fd[0]);
		p_fd[0] = -1;
	}
	close_fds(shell->cmd);
}
