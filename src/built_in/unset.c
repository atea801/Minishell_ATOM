/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:28:56 by aautret           #+#    #+#             */
/*   Updated: 2025/11/11 11:13:36 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"


int	check_args_unset(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (1);

	i = 1;
	if (str[0] == '_' || ft_isalpha((unsigned char)str[0]))
	{
		while (str[i])
		{
			if (ft_isalnum((unsigned char)str[i]) || str[i] == '_')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	check_valide_args_unset(t_minishell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->argv[i])
	{
		if (check_args_unset(shell->cmd->argv[i]) < 1)
			i++;
		else
			return (1);
	}
	return (0);
}


int	builtin_unset(t_minishell *shell)
{
	int	i;

	if (!shell->cmd->argv[1])
	{
		shell->exit_code = 0;
		return (0);
	}
	if (check_valide_args_unset(shell) != 0)
	{
		printf("parsing args unset\n");
		shell->exit_code = 1;
		return (1);
	}
	i = 1;
	while (shell->cmd->argv[i])
	{
		delete_node_list(&shell->env, shell->cmd->argv[i]);
		printf("%s delete\n", shell->cmd->argv[i]);
		i++;
	}
	shell->exit_code = 0;
	return (0);
}
