/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:01:05 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/08 16:06:32 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

char	*type_expand(char *res)
{
	int	i;

	i = 0;
	if (!res)
		return (NULL);
	
	// Vérifier si c'est exactement $?
	if (ft_strcmp(res, "$?") == 0)
		return ("EXPAND");
	
	// Vérifier si le token contient $? (comme $?$ ou $?hello)
	while (res[i])
	{
		if (res[i] == '$' && res[i + 1] == '?')
			return ("EXPAND");
		i++;
	}
	return (NULL);
}
