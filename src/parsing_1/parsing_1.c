/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:10:28 by aautret           #+#    #+#             */
/*   Updated: 2025/11/27 15:02:22 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	valide_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (1);
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '|' || str[i] == '\0')
				return (1);
		}
		else
			i++;
	}
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
	char	*res_3;

	res_3 = separate_exit_patterns(input);
	res_1 = add_space_to_operator(res_3);
	res_2 = clear_input(res_1);
	free(res_1);
	free(res_3);
	if (valide_pipe(res_2))
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n", 2);
		add_history(input);
		return (free(res_2), shell->exit_code = 2, NULL);
	}
	if (validate_quotes_improved(res_2))
	{
		ft_putstr_fd("Minishell: unclosed quotes\n", 2);
		add_history(input);
		return (free(res_2), shell->exit_code = 258, NULL);
	}
	return (res_2);
}
