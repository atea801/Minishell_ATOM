/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:07 by aautret           #+#    #+#             */
/*   Updated: 2025/09/25 15:16:25 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	count_redir(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			count++;
		i++;
	}
	return (count);
}

char	*add_redir_space(char *input)
{
	char	*res;
	int		count;
	int		i;
	int		j;

	count = count_redir(input);
	res = malloc(sizeof(char) * (ft_strlen(input) + count + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			res[j++] = ' ';
			res[j++] = input[i++];
			res[j++] = ' ';
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}
