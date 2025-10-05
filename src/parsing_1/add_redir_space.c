/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:30:07 by aautret           #+#    #+#             */
/*   Updated: 2025/10/05 13:42:38 by tlorette         ###   ########.fr       */
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
	res = malloc(sizeof(char) * (ft_strlen(input) + count * 2 + 1));
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

int	count_pipe(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

char	*add_pipe_space(char *input)
{
	char	*res;
	int		count;
	int		i;
	int		j;

	count = count_pipe(input);
	res = malloc(sizeof(char) * (ft_strlen(input) + count * 2 + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '|')
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

char	*add_space_to_operator(char *input)
{
	char	*res;
	char	*res1;

	res = add_redir_space(input);
	res1 = add_pipe_space(res);
	free(res);
	return (res1);
}
