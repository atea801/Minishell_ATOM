/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:30:31 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 12:57:27 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Gerer le cas de cd sans arguments (retourner dans HOME)
 * 
 * - verifie si HOME est accessible
 * - change de repertoire avec chdir
 * - update l'env
 * @param shell 
 * @param home 
 * @param old_pwd 
 * @param new_pwd 
 * @return int 0 = succes / 1 = erreur
 */
int	case_cd_sin_arg(t_minishell *shell, char *home, char *old_pwd,
		char *new_pwd)
{
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

/**
 * @brief Verifie et effectue le changemnt de chemin vers la valeur de
 * oldpwd recu depuis l'env
 * 
 * @param oldpwd_env 
 * @return int 0 = succes (chdir ok) / 1 = erreur
 */
static int	cd_special_dash_check_oldpwd(char	*oldpwd_env)
{
	if (chdir(oldpwd_env) != 0)
	{
		perror("Minishell: cd");
		return (1);
	}
	return (0);
}

/**
 * @brief Gere le cas cd - : aller dans oldpwd, affiche le nouveau 
 * cwd sur stdout et met a jour les variab;es d'env
 * 
 * cd - = repertoire precedent d'ou le oldpwd
 * @param shell 
 * @param old_pwd 
 * @param new_pwd 
 * @return int 
 */
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
	if (cd_special_dash_check_oldpwd(oldpwd_env) > 0)
	{
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

/**
 * @brief verifie l'existence et les permisions d'executions du path avec chdir
 * 
 * @param path 
 * @return int 0 = succes / 1 = erreur
 */
// static int	cd_with_args_check_access(char *path)
// {
// 	if (access(path, F_OK) != 0)
// 	{
// 		cd_with_args_error_print(path);
// 		return (1);
// 	}
// 	if (access(path, X_OK) != 0)
// 	{
// 		perror("Minishell: cd");
// 		return (1);
// 	}
// 	return (0);
// }

/**
 * @brief Gere le cas cd <path> quand un argument simple est donne
 * 
 * - change cwd
 * 
 * - met a jour OLDPWD et PWD
 * 
 * - free old_pwd + free path en succes ou erreur via args_free
 * 
 * @param shell 
 * @param old_pwd 
 * @param new_pwd 
 * @return int 
 */
int	cd_with_args(t_minishell *shell, char *old_pwd, char *new_pwd)
{
	char	*path;

	path = ft_strdup(shell->cmd->argv[1]);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("Minishell : cd :", 2);
		perror(path);
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
