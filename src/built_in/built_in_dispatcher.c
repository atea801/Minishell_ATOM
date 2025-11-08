/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:40:32 by aautret           #+#    #+#             */
/*   Updated: 2025/11/07 18:18:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Dispatche les appels des commande en fonction du built-in
 * detecte
 * 
 * @param cmd 
 * @return int n'est jamais sence return 1 car call dans le cas ou
 * is_builin == 1
 */
int	execute_builtin(t_minishell *shell)
{
	if (ft_strcmp(shell->cmd->argv[0], "echo") == 0)
		return (builtin_echo(shell));
	// if (ft_strcmp(shell->cmd->argv[0], "pwd") == 0)
	// 	return (builtin_pwd(shell));
	// if (ft_strcmp(shell->cmd->argv[0], "env") == 0)
	// 	return (builtin_env(shell));
	// if (ft_strcmp(shell->cmd->argv[0], "exit") == 0)
	// 	return (builtin_exit(shell));
	// if (ft_strcmp(shell->cmd->argv[0], "cd") == 0)
	// 	return (builtin_cd(shell));
	// if (ft_strcmp(cmd->argv[0], "export") == 0)
	// 	return (builtin_export(cmd));
	// if (ft_strcmp(cmd->argv[0], "unset") == 0)
	// 	return (builtin_unset(cmd));
	return (1);
}
