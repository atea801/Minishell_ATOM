/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/21 10:57:12 by aautret          ###   ########.fr       */
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
	else if (error  == 2)
	{
		print_redir_error(&t_head_1);
		return (2);
	}
	return (0);
}
