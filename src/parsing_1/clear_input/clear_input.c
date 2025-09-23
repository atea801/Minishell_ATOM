/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:21:03 by aautret           #+#    #+#             */
/*   Updated: 2025/09/23 17:48:18 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"


/**
 * @brief retire les epaces avant et pendant la chaine de caractere,
 * reecrit la chaine passee en arg et retourne une nouvelle version
 * de cette chaine
 *
 * @param input
 * @return char*
 */
char	*clear_input(char *input)
{
	int		i;
	int		j;
	int		flag;
	char	*res;

	i = skip_space(input);
	j = 0;
	flag = 0;
	res = malloc(sizeof(char) * (ft_strlen(input)
				- (count_space(input) - count_words(input))));
	if (!res)
		return (NULL);
	res = epur(input, res, i);
	return (res);
}
