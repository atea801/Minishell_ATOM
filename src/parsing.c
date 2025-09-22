/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:39:47 by aautret           #+#    #+#             */
/*   Updated: 2025/09/22 18:50:11 by aautret          ###   ########.fr       */
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


void	tokenizer(t_token *token, char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			res[j] = str[i];
			i++;
			j++;
		}
	}
	token->value = res;
	//type a checker
	token = token->next;
}
