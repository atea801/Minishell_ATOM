/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:40:33 by aautret           #+#    #+#             */
/*   Updated: 2025/11/26 11:29:38 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	execute_child_utils(t_minishell *shell, char **env, int num_cmd)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(": command not found\n", 2);
	free_env_tab(env);
	free_all_life(shell);
	free_pipes(shell->buffers.pipes, num_cmd - 1);
	exit(127);
}

int	exec_single_securities(t_minishell *shell)
{
	if (!shell->cmd || !shell->cmd->argv || !shell->cmd->argv[0])
		return (shell->exit_code = 0, 0);
	if (!shell->cmd->argv[0][0])
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_code = 127;
		return (0);
	}
	return (1);
}
