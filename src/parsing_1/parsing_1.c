/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:10:28 by aautret           #+#    #+#             */
/*   Updated: 2025/10/09 15:15:08 by tlorette         ###   ########.fr       */
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
int	valide_quote(char *str)
{
	int	i;
	int	flag_open;

	i = 0;
	flag_open = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			flag_open++;
		i++;
	}
	if (flag_open % 2 != 0)
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
 */
char	*parsing_1(char *input)
{
	char	*res_1;
	char	*res_2;

	res_1 = add_space_to_operator(input);
	printf("%s\n", res_1);
	res_2 = clear_input(res_1);
	free(res_1);
	if (valide_quote(res_2))
	{
		write(2, "unclosed quotes\n", 16);
		add_history(input);
		free(res_2);
		return (NULL);
	}
	return (res_2);
}
