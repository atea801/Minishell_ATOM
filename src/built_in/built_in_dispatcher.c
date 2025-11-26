/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:40:32 by aautret           #+#    #+#             */
/*   Updated: 2025/11/26 18:15:03 by aautret          ###   ########.fr       */
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
	if (ft_strcmp(shell->cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(shell));
	if (ft_strcmp(shell->cmd->argv[0], "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(shell->cmd->argv[0], "exit") == 0)
		return (builtin_exit(shell));
	if (ft_strcmp(shell->cmd->argv[0], "cd") == 0)
		return (builtin_cd(shell));
	if (ft_strcmp(shell->cmd->argv[0], "unset") == 0)
		return (builtin_unset(shell));
	if (ft_strcmp(shell->cmd->argv[0], "export") == 0)
		return (builtin_export(shell));
	return (1);
}

void	exec_built_in_child(t_minishell *shell, char **env, int num_cmd,
		t_cmd *cmd)
{
	int	exit_code;

	exit_code = execute_builtin(shell);
	free_cmd_list(cmd);
	cmd = NULL;
	shell->cmd = NULL;
	free_in_child(shell, env, num_cmd);
	exit(exit_code);
}
