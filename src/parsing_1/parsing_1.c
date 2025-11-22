/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:10:28 by aautret           #+#    #+#             */
/*   Updated: 2025/11/22 14:47:41 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief checke si une single/double quote est ouverte ou fermee
 *
 * return 1 => PAS FERMEE
 * return 0 => FERMEE
 *
 * @param str
 * @return int
 */
// int	valide_quote(char *str)
// {
// 	int	i;
// 	int	flag_open;

// 	i = 0;
// 	flag_open = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 39 || str[i] == 34)
// 			flag_open++;
// 		i++;
// 	}
// 	if (flag_open % 2 != 0)
// 		return (1);
// 	return (0);
// }

/**
 * @brief Version améliorée de valide_quote avec state machine
 *
 * AMÉLIORATION MAJEURE : Au lieu de compter les quotes, utilise une
 * state machine qui comprend les règles d'imbrication bash
 *
 * RÈGLES GÉRÉES :
 * - Dans des quotes simples : les doubles sont littérales
 * - Dans des quotes doubles : les simples sont littérales
 * - Détection précise des quotes non fermées
 *
 * @param str Chaîne à valider
 * @return int 1 si quotes non fermées, 0 si OK (MÊME INTERFACE que l'original)
 */
int	validate_quotes_improved(char *str)
{
	t_quote_state_simple	state;
	int						i;

	if (!str)
		return (1);
	i = 0;
	state = STATE_NORMAL;
	while (str[i])
	{
		if (str[i] == '\'' && state != STATE_DOUBLE)
		{
			// Toggle state pour quotes simples (sauf si dans doubles)
			if (state == STATE_SINGLE)
				state = STATE_NORMAL;
			else
				state = STATE_SINGLE;
		}
		else if (str[i] == '"' && state != STATE_SINGLE)
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

static int	valide_pipe(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '|')
			count++;
	}
	if (count > 1)
		return (1);
	return (0);
}

/**
 * @brief Premier passage du parsing
 *
 * - clear input => revoie une chaine de caracteres au format
 * attendu pour tokenisation / lecture
 * (sans espaces superflues)
 *
 * @param input
 * @return char*
 * @note Utilisation de la version améliorée dans le if
 */
char	*parsing_1(t_minishell *shell, char *input)
{
	char	*res_1;
	char	*res_2;

	res_1 = add_space_to_operator(input);
	res_2 = clear_input(res_1);
	free(res_1);
	if (valide_pipe(res_2))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n", 2);
		add_history(input);
		free(res_2);
		shell->exit_code = 2;
		return (NULL);
	}
	if (validate_quotes_improved(res_2))
	{
		ft_putstr_fd("Minishell: unclosed quotes\n", 2);
		add_history(input);
		free(res_2);
		shell->exit_code = 258;
		return (NULL);
	}
	return (res_2);
}
