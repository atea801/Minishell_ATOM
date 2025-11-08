/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:05:59 by aautret           #+#    #+#             */
/*   Updated: 2025/11/08 11:47:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Parse les options -n de la commande echo
 *
 * Parcourt les arguments pour identifier les flags
	-n valides (suppression du newline).
 * S'arrête au premier argument qui n'est pas un flag
	-n ou qui ne commence pas par '-'.
 *
 * @param cmd Structure contenant la commande et ses arguments

	* @return Index du premier argument non-flag (où commencent les textes à afficher)
 * @example echo_parser(cmd) retourne 2 pour "echo -n hello world"
 */
int	echo_parser(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv[i] && cmd->argv[i][0] == '-')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != 0)
			return (i);
		i++;
	}
	return (i);
}

int	check_echo_dollar(t_minishell *shell)
{
	int		start_arg;
	t_token	*current;

	if (!shell || !shell->cmd || !shell->cmd->argv)
		return (0);
	// Vérifier dans tok1 (avant expansion) s'il y a un $ seul
	current = shell->tok1;
	while (current)
	{
		if (current->value && ft_strcmp(current->value, "$") == 0)
		{
			// Vérifier que c'est le seul argument après echo
			start_arg = echo_parser(shell->cmd);
			if (shell->cmd->argc == start_arg + 1)
			{
				if (start_arg > 1) // Il y a des flags -n
					printf("$");
				else
					printf("$\n");
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	search_dollar_in_list(t_token *tok1)
{
	t_token	*token1;
	int		count;

	token1 = tok1;
	count = 0;
	if (!tok1)
		return (0);
	while (token1)
	{
		if (token1->value && ft_strcmp(token1->value, "$") == 0)
			return (count);
		token1 = token1->next;
		count++;
	}
	return (-1);
}

int	restore_dollar_in_argv(t_minishell *shell)
{
	int	start_arg;
	int	dollar_tok1;
	int	dollar_pos;
	int	argv_index;

	if (!shell || !shell->tok1 || !shell->cmd || !shell->cmd->argv)
		return (0);
	dollar_tok1 = search_dollar_in_list(shell->tok1);
	if (dollar_tok1 < 0)
		return (0);
	start_arg = echo_parser(shell->cmd);
	dollar_pos = dollar_tok1 - start_arg;
	argv_index = start_arg + dollar_pos;
	if (argv_index >= start_arg && argv_index < shell->cmd->argc)
	{
		free(shell->cmd->argv[argv_index]);
		shell->cmd->argv[argv_index] = ft_strdup("$");
		return (1);
	}
	return (0);
}

int	builtin_echo(t_minishell *shell)
{
	int	i;
	int	flag;

	if (!shell->cmd || !shell->cmd->argv || !shell->cmd->argv[0])
		return (1);
	if (ft_strcmp(shell->cmd->argv[0], "echo") != 0)
		return (1);
	restore_dollar_in_argv(shell);
	if (check_echo_dollar(shell))
		return (0);
	i = 1;
	flag = 0;
	if (echo_parser(shell->cmd) > 1)
	{
		flag = 1;
		i = echo_parser(shell->cmd);
	}
	while (shell->cmd->argv[i])
	{
		printf("%s", shell->cmd->argv[i]);
		if (shell->cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

int	echo_completed(t_minishell *shell)
{
	if (!shell->cmd)
		return (1);
	while (shell->cmd)
	{
		builtin_echo(shell);
		shell->cmd = shell->cmd->next;
	}
	return (0);
}
