/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:35:15 by aautret           #+#    #+#             */
/*   Updated: 2025/11/04 16:15:14 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	cd_init_vars(t_minishell *shell, char **home, char **oldpwd)
{
	*home = search_in_list(&shell->env, "HOME");
	*oldpwd = getcwd(NULL, 0);
	if (!*home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!*oldpwd)
	{
		perror("Minishell: getcwd");
		return (1);
	}
	return (0);
}

int	cd_dispatch_case(t_minishell *shell, char *home, char *oldpwd,
		char *new_pwd)
{
	if (shell->cmd->argc == 1)
		return (case_cd_sin_arg(shell, home, oldpwd, new_pwd));
	if (shell->cmd->argc == 2 && ft_strcmp(shell->cmd->argv[1], "-") == 0)
		return (cd_special_case_dash(shell, oldpwd, new_pwd));
	if (shell->cmd->argc == 2 && ft_strcmp(shell->cmd->argv[1], "~") == 0)
		return (case_cd_sin_arg(shell, home, oldpwd, new_pwd));
	if (shell->cmd->argc == 2)
		return (cd_with_args(shell, oldpwd, new_pwd));
	if (shell->cmd->argc > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_minishell *shell)
{
	char	*home;
	char	*oldpwd;
	char	new_pwd[BUFFER_SIZE];

	if (cd_init_vars(shell, &home, &oldpwd) == 1)
		return (1);
	return (cd_dispatch_case(shell, home, oldpwd, new_pwd));
}
