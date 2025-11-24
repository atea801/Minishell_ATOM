/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:20:58 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 10:52:37 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"
#include <limits.h>

int	atol_utils(char *str, int i, long res, int sign)
{
	if (!ft_isdigit(str[i]))
		return (0);
	if (res > LONG_MAX / 10)
		return (0);
	if (res == LONG_MAX / 10)
	{
		if (sign == 1 && (str[i] - '0') > LONG_MAX % 10)
			return (0);
		if (sign == -1 && (str[i] - '0') > -(LONG_MIN % 10))
			return (0);
	}
	return (1);
}

/**
 * @brief Convertit une string en long avec detection d'overflow
 *
 * @param str La string a convertir
 * @param result Pointeur pour stocker le resultat
 * @return int 1 si succès, 0 si overflow ou erreur
 */
static int	ft_atol_safe(char *str, long *result)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (atol_utils(str, i, res, sign) == 0)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	*result = res * sign;
	return (1);
}

/**
 * @brief Affiche le bon message d'erruer si l'arg fourni n'est pas numeric
 *
 * @param shell
 */
static void	print_message_exit(t_minishell *shell)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	write(2, shell->cmd->argv[1], ft_strlen(shell->cmd->argv[1]));
	ft_putstr_fd(": numeric argument required\n", 2);
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
	long	code_long;
	int		code;

	printf("exit\n");
	if (shell->cmd->argv[1] == NULL)
	{
		shell->should_exit = true;
		return (0);
	}
	if (!ft_atol_safe(shell->cmd->argv[1], &code_long))
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
	code = (int)code_long;
	code = calc_code(code);
	shell->exit_code = code;
	shell->should_exit = true;
	return (code);
}
