/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:40:33 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 15:44:57 by aautret          ###   ########.fr       */
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
