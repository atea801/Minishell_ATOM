/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:05:09 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 11:07:09 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	var_len(char *s, int start)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (ft_isalnum(s[start + i]) || s[start + i] == '_')
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	free(s2);
	return (res);
}
