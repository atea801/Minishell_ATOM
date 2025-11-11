/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:17:34 by aautret           #+#    #+#             */
/*   Updated: 2025/11/11 15:46:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	cd_update_env(t_minishell *shell, char *old_pwd, char *new_pwd)
{
	change_node_list(&shell->env, "OLDPWD", old_pwd);
	change_node_list(&shell->env, "PWD", new_pwd);
	free(old_pwd);
}

void	cd_with_args_free(char *old_pwd, char *path)
{
	free(old_pwd);
	free(path);
}

void	cd_with_args_error_print(char *path)
{
	ft_putstr_fd("Minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
