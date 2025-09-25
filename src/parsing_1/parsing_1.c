/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:10:28 by aautret           #+#    #+#             */
/*   Updated: 2025/09/23 17:48:31 by aautret          ###   ########.fr       */
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
	char	*res;

	res = clear_input(input);
	printf("res = %s\n", res);
	return (res);
}
