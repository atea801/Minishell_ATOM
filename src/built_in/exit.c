/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:20:58 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 15:51:18 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_minishell *shell)
{
	int	code;

	printf("exit\n");
	if (shell->cmd->argv[1] == NULL)
		exit(shell->exit_code);
	if (shell->cmd->argv[2])
	{
		write(2, "Atom: exit: too many arguments\n", 31);
		shell->exit_code = 1;
		return (1);
	}
	if (!ft_is_numeric(shell->cmd->argv[1]))
	{
		write(2, "Atom: exit: ", 12);
		write(2, shell->cmd->argv[1], ft_strlen(shell->cmd->argv[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	code = ft_atoi(shell->cmd->argv[1]);
	if (code < 0)
		code = (code % 256) + 256;
	else
		code = code % 256;
	exit(code);
}
