/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multipipe_heredoc_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:07 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/27 14:33:35 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	close_unused_fd0_heredoc(int *p_fd, int index, t_cmd *cmd)
{
	if (p_fd[0] != -1)
	{
		if (index != cmd->count_heredocs - 1)
			close(p_fd[0]);
		else
			cmd->fd_in = p_fd[0];
	}
}

void	close_unused_fd1_heredoc(int *p_fd, int index, t_cmd *cmd)
{
	if (index != cmd->count_heredocs - 1)
	{
		close(p_fd[0]);
	}
	else
		cmd->fd_in = p_fd[0];
}

void	check_closing_fd(int *p_fd, int index, t_cmd *cmd)
{
	if (p_fd[0] != -1)
		close_unused_fd1_heredoc(p_fd, index, cmd);
	if (p_fd[1] != -1)
		close(p_fd[1]);
}
