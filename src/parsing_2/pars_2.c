/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/17 11:12:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"


/**
 * @brief Vérifie la validité syntaxique et prépare les tokens pour l'exécution.
 *
 * - Vérifie la syntaxe globale (pipes, redirections seules, erreurs de tokens)
 * 
 * - Si une erreur est détectée, retourne 1 et arrête le parsing
 * 
 * - Si aucune erreur, lance tokenizer_2 pour préparer l'exécution
 *
 * 
 * @param token_head liste de tokens générée lors du premier parsing
 * @param token_2 
 * @return int 
 */
int	parsing_2(t_token *token_head, t_token_2 *token_2)
{
	t_token_2	*t_head_2;
	t_token		*t_head_1;
	int			error;

	t_head_1 = token_head;
	t_head_2 = token_2;
	error = check_all(&t_head_1);
	if (error == 1)
		return (1);
	else if (error == 0)
		tokenizer_2(t_head_1, t_head_2);
	return (0);
}
