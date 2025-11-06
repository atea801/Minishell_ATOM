/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:37 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/06 13:26:03 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_pid_error(int **pipes, int num_cmd)
{
	close_all_pipes(pipes, num_cmd - 1);
	free_pipes(pipes, num_cmd - 1);
	return (0);
}

int	cleanup_on_error(int **pipes, pid_t *pids, int num_cmd,
		t_minishell *shell)
{
	close_all_pipes(pipes, num_cmd - 1);
	wait_all_childrens(pids, num_cmd, shell);
	free_pipes(pipes, num_cmd - 1);
	free(pids);
	return (1);
}

