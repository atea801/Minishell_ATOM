/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:28:56 by aautret           #+#    #+#             */
/*   Updated: 2025/11/11 16:03:06 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	check_speacial_unset(t_minishell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->argv[i])
	{
		if (shell->cmd->argv[i][0] == '-')
		{
			ft_putstr_fd("Minishell: unset: ", 2);
			ft_putstr_fd(&shell->cmd->argv[i][0], 2);
			ft_putstr_fd(&shell->cmd->argv[i][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			ft_putstr_fd("unset: usage: unset [-f] [-v] [-n] [name ...]\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_args_unset(char *str)
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

static void	unset(t_minishell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->argv[i])
	{
		if (search_in_list(&shell->env, shell->cmd->argv[i]) != NULL
			&& shell->cmd->argv[i])
		{
			if (check_args_unset(shell->cmd->argv[i]) == 0)
			{
				delete_node_list(&shell->env, shell->cmd->argv[i]);
				printf("%s delete\n", shell->cmd->argv[i]);
			}
		}
		i++;
	}
}

int	builtin_unset(t_minishell *shell)
{
	if (!shell->cmd->argv[1])
	{
		shell->exit_code = 0;
		return (0);
	}
	if (check_speacial_unset(shell) == 1)
	{
		shell->exit_code = 0;
		return (0);
	}
	else
		unset(shell);
	shell->exit_code = 0;
	return (0);
}
