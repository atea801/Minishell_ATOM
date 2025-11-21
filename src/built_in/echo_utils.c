/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:40:29 by aautret           #+#    #+#             */
/*   Updated: 2025/11/21 13:50:14 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Parse les options -n de la commande echo
 *
 * Parcourt les arguments pour identifier les flags
 * -n valides (suppression du newline).
 * S'arrête au premier argument qui n'est pas un flag
 * -n ou qui ne commence pas par '-'.
 *
 * @param cmd Structure contenant la commande et ses arguments
 * @return Index du premier argument non-flag (où commencent
 les textes à afficher)
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

/**
 * @brief Cherche la première occurrence d'un token
 * dont value est exactement "$" dans la liste tok1 et
 * retourne sa position (index).
 *
 *  - Itère sur la liste et incrémente un compteur;
 * si token->value est "$", retourne le compteur.
 * @param tok1
 * @return int index du token $ (0-based) s'il existe, -1 sinon.
 */
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

void	print_echo_args(t_cmd *cmd, int out_fd, int start)
{
	int	i;

	i = start;
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], out_fd);
		if (cmd->argv[i + 1])
			ft_putchar_fd(' ', out_fd);
		i++;
	}
}
