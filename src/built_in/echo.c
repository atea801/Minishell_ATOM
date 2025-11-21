/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:05:59 by aautret           #+#    #+#             */
/*   Updated: 2025/11/21 13:50:03 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Gestion cas speacial avec $
 *
 * - Si l'appel echo ne recoit que ce $ comme unique argument
 *  (apres des flags aussi)
 *
 * - On affiche $ avc ou sans newline selon presence de -n
 *
 * @param shell
 * @note but = gestion du cas echo $
 * @return int 1 = cas special detecte et traite
 */
int	check_echo_dollar(t_minishell *shell)
{
	int		start_arg;
	t_token	*current;

	if (!shell || !shell->cmd || !shell->cmd->argv)
		return (0);
	current = shell->tok1;
	while (current)
	{
		if (current->value && ft_strcmp(current->value, "$") == 0)
		{
			start_arg = echo_parser(shell->cmd);
			if (shell->cmd->argc == start_arg + 1)
			{
				if (start_arg > 1)
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

static void	restore_dollar_utils(t_token *current, t_minishell *shell,
		int argv_index)
{
	if (current->value && ft_strcmp(current->value, "$") == 0)
	{
		free(shell->cmd->argv[argv_index]);
		shell->cmd->argv[argv_index] = ft_strdup("$");
	}
}

/**
 * @brief Apres les etapes d'expansion,
 * il faut restaurer les arg qui devaient contenir le symbole $
 * (si ils ont ete supprimes)
 *
 * - calcul l'index du premier argv
 *
 * - parcours tok1 pour sauter les tok correspondant a echo  et les flags
 *
 * - parcours et comparaison en simultane si token->value = "$"  -> restaure
 *
 * @param shell
 * @note la fonciton modifie la shell->cmd->argv et alloue de nouvellle
 * chaine pour placer le $
 * @return int 1 = en fin (si le spoineurs de base sont valides) /
 * 0 = si le spointeurs d'entree sont invlaides
 */
int	restore_dollar_in_argv(t_minishell *shell)
{
	int		start_arg;
	t_token	*current;
	int		argv_index;

	if (!shell || !shell->tok1 || !shell->cmd || !shell->cmd->argv)
		return (0);
	start_arg = echo_parser(shell->cmd);
	current = shell->tok1;
	argv_index = 0;
	while (current && argv_index < start_arg)
	{
		if (current->value && (ft_strcmp(current->value, "echo") == 0
				|| (current->value[0] == '-')))
			argv_index++;
		current = current->next;
	}
	argv_index = start_arg;
	while (current && argv_index < shell->cmd->argc)
	{
		restore_dollar_utils(current, shell, argv_index);
		current = current->next;
		argv_index++;
	}
	return (1);
}

/**
 * @brief mplémentation du builtin echo: gère les flags -n,
 * restaure $ littéral si nécessaire,
 * imprime les arguments séparés par un espace,
 * et conditionnellement ajoute un newline.
 *
 * @param shell
 * @return int 0 = success / 1 = entre invalide
 */
int	builtin_echo(t_minishell *shell)
{
	int	i;
	int	flag;
	int	out_fd;

	if (!shell->cmd || !shell->cmd->argv || !shell->cmd->argv[0])
		return (1);
	if (ft_strcmp(shell->cmd->argv[0], "echo") != 0)
		return (1);
	restore_dollar_in_argv(shell);
	if (shell->cmd->fd_out != -1)
		out_fd = shell->cmd->fd_out;
	else
		out_fd = 1;
	i = 1;
	flag = 0;
	if (echo_parser(shell->cmd) > 1)
	{
		flag = 1;
		i = echo_parser(shell->cmd);
	}
	print_echo_args(shell->cmd, out_fd, i);
	if (flag == 0)
		ft_putchar_fd('\n', out_fd);
	return (0);
}

/**
 * @brief Parcourt la liste de commandes chaineeeds et
 * execute builtin_echo pour chaque elements
 *
 * @param shell
 * @note modifie l'etat de cmd dans certains cas
 * @return int toujours 0 sauf si shell-<cmd est NULL
 */
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
