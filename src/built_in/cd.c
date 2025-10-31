/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:35:15 by aautret           #+#    #+#             */
/*   Updated: 2025/10/31 16:48:04 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	builtin_cd(t_minishell *shell)
{
	char *home;
	char *oldpwd;
	char new_pwd[BUFFER_SIZE];

	oldpwd = NULL;
	// cas 1 sans args
	if (shell->cmd->argc == 1)
	{
		home = search_in_list(&shell->env, "HOME");
		if (!home)
		{
			ft_putstr_fd("Atom: cd: HOME not set\n", 2);
			return (1);
		}
		oldpwd = getcwd(NULL, 0);
		if (!oldpwd)
		{
			perror("getcwd");
			return (1);
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			free(oldpwd);
			return (1);
		}
		if (!getcwd(new_pwd, BUFFER_SIZE))
		{
			perror("getcwd");
			free(oldpwd);
			return (1);
		}
		change_node_list(&shell->env, "OLDPWD", oldpwd);
		change_node_list(&shell->env, "PWD", new_pwd);
		free(oldpwd);
		return (0);
	}
	return (0);
}