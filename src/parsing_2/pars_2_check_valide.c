/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_check_valide.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:12:52 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 19:17:19 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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
			|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0))
		&& t_head_2->next == NULL)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
		t_head_2 = t_head_2->next;
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0)
		|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0))
		return (1);
	return (0);
}


/**
 * @brief Détecte si la liste commence ou finit par un pipe,
 * ou si deux pipes se suivent, ce qui indique une erreur de syntaxe.
 *
 * @param token_2
 * @return int
 */
int	check_pipe(t_token *token_2)
{
	t_token	*t_head_2;

	t_head_2 = token_2;
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

/**
 * @brief Vérifie la présence d'erreurs dans la liste de tokens.
 *
 * Parcourt la liste de tokens et retourne 1 si un token possède le type "ERROR".
 * Sinon, retourne 0.
 * 
 * @param token_head 
 * @return int 
 */
int	check_error(t_token *token_head)
{
	t_token	*t_head_1;

	t_head_1 = token_head;
	while (t_head_1 && t_head_1->type)
	{
		if (ft_strcmp(t_head_1->type, "ERROR") == 0)
			return (1);
		t_head_1 = t_head_1->next;
	}
	return (0);
}

/**
 * @brief Vérifie la validité globale de la liste de tokens.
 *
 * - Appelle les différents checkers pour valider la syntaxe des tokens
 * @param token_2
 * @return int
 */
int	check_all(t_token **token_head)
{
	t_token	*t_head_1;

	if (!token_head || !*token_head)
		return (0);
	t_head_1 = *token_head;
	if (check_pipe(t_head_1) > 0)
		return (1);
	else if ((parse_redir_alone(&t_head_1) > 0))
		return (1);
	else if (check_error(t_head_1) > 0)
		return (1);
	return (0);
}