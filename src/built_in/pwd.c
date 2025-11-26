/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:07:37 by aautret           #+#    #+#             */
/*   Updated: 2025/11/26 11:41:04 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Permet de detecter les cas speciaux avec une option
 *
 *
 * @param shell
 * @return int
 */
static int	pwd_invalid_kind(char *arg)
{
	int	j;
	int	dash_count;

	if (!arg)
		return (0);
	if (ft_strcmp(arg, "--") == 0)
		return (2);
	dash_count = 0;
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '-')
			dash_count++;
		j++;
	}
	if (dash_count >= 2)
		return (2);
	if (dash_count == 1)
		return (1);
	return (0);
}

static int	pwd_parser(t_minishell *shell)
{
	int		kind;
	char	*arg;

	if (!shell || !shell->cmd || !shell->cmd->argv)
		return (1);
	arg = shell->cmd->argv[1];
	if (!arg)
		return (0);
	kind = pwd_invalid_kind(arg);
	if (kind == 2)
	{
		ft_putstr_fd("Minishell: pwd: --: invalid option\n", 2);
		ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
		return (1);
	}
	if (kind == 1)
	{
		ft_putstr_fd("Minishell: pwd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("Minishell: usage: pwd [-LP]\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief Affiche le repertoire de travail actuel
 *
 * @param cmd
 * @return int 0 == success 1 == erreur
 */
int	builtin_pwd(t_minishell *shell)
{
	char	buffer[BUFFER_SIZE];

	if (pwd_parser(shell) == 1)
	{
		return (1);
	}
	if (access(".", F_OK) != 0)
	{
		perror("Minishell: pwd:");
		return (1);
	}
	if (!getcwd(buffer, BUFFER_SIZE))
	{
		perror("Minishell: pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
