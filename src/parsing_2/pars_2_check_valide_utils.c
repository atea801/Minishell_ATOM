/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_check_valide_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:30 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 13:42:54 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Vérifie la présence d'erreurs dans la liste de tokens.
 *

	* Parcourt la liste de tokens et retourne 1 si un token possède le type "ERROR".
 * Sinon, retourne 0.
 *
 * @param token_head
 * @return char *
 */
t_token	*check_error(t_token *token_head)
{
	t_token	*t_head_1;

	t_head_1 = token_head;
	while (t_head_1 && t_head_1->type)
	{
		if (ft_strcmp(t_head_1->type, "ERROR") == 0)
			return (t_head_1);
		t_head_1 = t_head_1->next;
	}
	return (NULL);
}

/**
 * @brief Vérifie si une redirection est seule dans la liste de tokens.
 *
 * - Détecte si "REDIR_IN" "REDIR_OUT" sans argument
 *
 * - Retourne 1 si une redirection est seule (erreur de syntaxe), 0 sinon.
 *
 * @param token_2
 * @return int
 */
int	parse_redir_alone(t_token **token_2)
{
	t_token	*t_head_2;

	t_head_2 = *token_2;
	if (!t_head_2 || !t_head_2->type || !t_head_2->next)
		return (0);
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0
			|| ft_strcmp(t_head_2->type, "REDIR_OUT") == 0
			|| ft_strcmp(t_head_2->type, "HEREDOC") == 0
			|| ft_strcmp(t_head_2->type, "APPEND") == 0
			|| ft_strcmp(t_head_2->type, "HERESTRING") == 0)
		&& t_head_2->next == NULL)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
		t_head_2 = t_head_2->next;
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0)
		|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0)
		|| (ft_strcmp(t_head_2->type, "HEREDOC") == 0)
		|| (ft_strcmp(t_head_2->type, "APPEND") == 0)
		|| (ft_strcmp(t_head_2->type, "HERESTRING") == 0))
		return (1);
	return (0);
}
