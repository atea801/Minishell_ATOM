/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:02:31 by aautret           #+#    #+#             */
/*   Updated: 2025/10/09 16:37:53 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Vérifie la validité globale de la liste de tokens.
 *
 * - Appelle les différents checkers pour valider la syntaxe des tokens
 * @param token_2
 * @return int
 */
int	check_all(t_token_2 **token_2)
{
	t_token_2	*t_head_2;
	int			pipe_check;

	if (!token_2 || !*token_2)
		return (0);
	t_head_2 = *token_2;
	pipe_check = check_pipe(&t_head_2);
	return (pipe_check);
}

/**
 * @brief Détecte si la liste commence ou finit par un pipe,
 * ou si deux pipes se suivent, ce qui indique une erreur de syntaxe.
 *
 * @param token_2
 * @return int
 */
int	check_pipe(t_token_2 **token_2)
{
	t_token_2	*t_head_2;

	t_head_2 = *token_2;
	if (!t_head_2 || !t_head_2->type)
		return (0);
	if (ft_strcmp(t_head_2->type, "PIPE") == 0)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
	{
		if (ft_strcmp(t_head_2->type, "PIPE") == 0
			&& ft_strcmp(t_head_2->next->type, "PIPE") == 0)
			return (1);
		t_head_2 = t_head_2->next;
	}
	if (ft_strcmp(t_head_2->type, "PIPE") == 0)
		return (1);
	return (0);
}
