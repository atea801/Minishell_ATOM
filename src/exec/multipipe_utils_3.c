/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:20:42 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/24 14:58:17 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	write_ctrld_error_msg(t_minishell *shell, char *delimiter, int *p_fd)
{
	(void)shell;
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
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
	free_all_life(shell);
}

void	free_and_close_before_delim(t_minishell *shell, char *line, int *p_fd)
{
	(void)shell;
	free(line);
	if (p_fd && p_fd[1] != -1)
	{
		close(p_fd[1]);
		p_fd[1] = -1;
	}
}

void	path_not_found_exe_child(t_minishell *shell, t_cmd *cmd, int num_cmd,
		char **env)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_env_tab(env);
	free_all_life(shell);
	free_pipes(shell->buffers.pipes, num_cmd - 1);
	exit(127);
}
