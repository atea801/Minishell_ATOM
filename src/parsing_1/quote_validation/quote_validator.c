/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:00:00 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 10:34:00 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	quotes_validator_single(t_quote_state_simple *state)
{
	if (*state == STATE_SINGLE)
		*state = STATE_NORMAL;
	else
		*state = STATE_SINGLE;
}

static void	quotes_validator_double(t_quote_state_simple *state)
{
	if (*state == STATE_DOUBLE)
		*state = STATE_NORMAL;
	else
		*state = STATE_DOUBLE;
}

/**
 * @brief Verifie si la chaine contient des quotes non fermees
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
 * @return int 1 si quotes non fermées, 0 toutes les quotes sont fermees
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
			quotes_validator_single(&state);
		}
		else if (input[i] == '"' && state != STATE_SINGLE)
		{
			quotes_validator_double(&state);
		}
		i++;
	}
	if (state != STATE_NORMAL)
		return (1);
	return (0);
}
