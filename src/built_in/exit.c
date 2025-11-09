/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:20:58 by aautret           #+#    #+#             */
/*   Updated: 2025/11/09 13:20:09 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Verifie que l'arg est bien un code numeric 
 * et ne contient pas de caractere non numeric
 * 
 * @param str 
 * @return int 
 */
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

/**
 * @brief Affiche le bon message d'erruer si l'arg fourni n'est pas numeric
 * 
 * @param shell 
 */
static void	print_message_exit(t_minishell *shell)
{
	write(2, "Minishell: ", 11);
	write(2, shell->cmd->argv[1], ft_strlen(shell->cmd->argv[1]));
	write(2, ": numeric argument required\n", 28);
	shell->exit_code = 2;
	shell->should_exit = true;
}

/**
 * @brief Calcul du code si code > 255
 * 
 * @param code 
 * @return int 
 */
static int	calc_code(int code)
{
	if (code < 0)
		code = (code % 256) + 256;
	else
		code = code % 256;
	return (code);
}

int	builtin_exit(t_minishell *shell)
{
	int	code;

	printf("exit\n");
	if (shell->cmd->argv[1] == NULL)
	{
		shell->should_exit = true;
		return (0);
	}
	if (!ft_is_numeric(shell->cmd->argv[1]))
	{
		print_message_exit(shell);
		return (2);
	}
	if (shell->cmd->argv[2])
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		shell->exit_code = 1;
		return (1);
	}
	code = ft_atoi(shell->cmd->argv[1]);
	code = calc_code(code);
	shell->exit_code = code;
	shell->should_exit = true;
	return (code);
}
