/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:30:31 by aautret           #+#    #+#             */
/*   Updated: 2025/11/05 16:24:50 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	case_cd_sin_arg(t_minishell *shell, char *home, char *old_pwd,
		char *new_pwd)
{
	if (access(home, F_OK) != 0)
	{
		perror("Minishell: cd");
		free(old_pwd);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("Minishell: cd");
		free(old_pwd);
		return (1);
	}
	if (!getcwd(new_pwd, BUFFER_SIZE))
	{
		perror("Minishell: getcwd");
		free(old_pwd);
		return (1);
	}
	cd_update_env(shell, old_pwd, new_pwd);
	return (0);
}

int	cd_special_case_dash(t_minishell *shell, char *old_pwd, char *new_pwd)
{
	char	*oldpwd_env;

	oldpwd_env = search_in_list(&shell->env, "OLDPWD");
	if (!oldpwd_env)
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
		free(old_pwd);
		return (1);
	}
	if (access(oldpwd_env, F_OK) != 0)
	{
		perror("Minishell: cd");
		free(old_pwd);
		return (1);
	}
	if (chdir(oldpwd_env) != 0)
	{
		perror("Minishell: cd");
		free(old_pwd);
		return (1);
	}
	if (!getcwd(new_pwd, BUFFER_SIZE))
	{
		perror("Minishell: getcwd");
		free(old_pwd);
		return (1);
	}
	ft_putstr_fd(new_pwd, 1);
	ft_putstr_fd("\n", 1);
	cd_update_env(shell, old_pwd, new_pwd);
	return (0);
}

int	cd_with_args(t_minishell *shell, char *old_pwd, char *new_pwd)
{
	char	*path;

	path = ft_strdup(shell->cmd->argv[1]);
	if (access(path, F_OK) != 0)
	{
		cd_with_args_error_print(path);
		cd_with_args_free(old_pwd, path);
		return (1);
	}
	if (access(path, X_OK) != 0)
	{
		perror("Minishell: cd");
		cd_with_args_free(old_pwd, path);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("Minishell: cd");
		cd_with_args_free(old_pwd, path);
		return (1);
	}
	if (!getcwd(new_pwd, BUFFER_SIZE))
	{
		perror("Minishell: getcwd");
		cd_with_args_free(old_pwd, path);
		return (1);
	}
	cd_update_env(shell, old_pwd, new_pwd);
	free(path);
	return (0);
}
