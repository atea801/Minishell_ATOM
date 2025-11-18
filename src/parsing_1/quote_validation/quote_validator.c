/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:00:00 by aautret           #+#    #+#             */
/*   Updated: 2025/11/18 14:48:41 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../atom.h"

/**
 * @brief Drop-in replacement pour valide_quote()
 * 
 * AMÉLIORATION MAJEURE : Au lieu de compter les quotes, on utilise une 
 * state machine qui comprend les règles d'imbrication
 * 
 * RÈGLES GÉRÉES :
 * - Dans des quotes simples : les doubles sont littérales
 * - Dans des quotes doubles : les simples sont littérales  
 * - Détection précise des quotes non fermées
 * 
 * @param input Chaîne à valider
 * @return int 1 si quotes non fermées, 0 si OK (MÊME INTERFACE que l'original)
 */
int	validate_quotes_improved(char *input)
{
	int						i;
	t_quote_state_simple	state;

	if (!input)
		return (1);
	i = 0;
	state = STATE_NORMAL;
	while (input[i])
	{
		if (input[i] == '\'' && state != STATE_DOUBLE)
		{
			// Toggle state pour quotes simples (sauf si dans doubles)
			if (state == STATE_SINGLE)
				state = STATE_NORMAL;
			else
				state = STATE_SINGLE;
		}
		else if (input[i] == '"' && state != STATE_SINGLE)
		{
			// Toggle state pour quotes doubles (sauf si dans simples)
			if (state == STATE_DOUBLE)
				state = STATE_NORMAL;
			else
				state = STATE_DOUBLE;
		}
		i++;
	}
	// Retourne 1 si pas fermé (comme l'original)
	if (state != STATE_NORMAL)
		return (1);
	return (0);
}
