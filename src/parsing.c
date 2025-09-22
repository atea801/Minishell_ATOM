/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:39:47 by aautret           #+#    #+#             */
/*   Updated: 2025/09/22 17:18:01 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../atom.h"

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
