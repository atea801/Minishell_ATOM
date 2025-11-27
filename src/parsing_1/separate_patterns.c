/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_patterns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:59:15 by aautret           #+#    #+#             */
/*   Updated: 2025/11/27 15:04:56 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	is_exit_pattern(const char *s, int i)
{
	if (!s[i] || !s[i + 1])
		return (0);
	return (s[i] == '$' && s[i + 1] == '?');
}

static char	*alloc_sep_res(const char *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = strlen(s);
	return (malloc(len * 2 + 1));
}

static void	write_exit_pattern(char *res, size_t *j)
{
	res[(*j)++] = '$';
	res[(*j)++] = '?';
}

static void	maybe_insert_space(const char *s, size_t i,
		char *res, size_t *j)
{
	if (is_exit_pattern(s, i))
		res[(*j)++] = ' ';
}

char	*separate_exit_patterns(const char *s)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s)
		return (NULL);
	res = alloc_sep_res(s);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_exit_pattern(s, i))
		{
			write_exit_pattern(res, &j);
			i += 2;
			maybe_insert_space(s, i, res, &j);
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
