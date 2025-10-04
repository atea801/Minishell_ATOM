/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:47:58 by codespace         #+#    #+#             */
/*   Updated: 2025/10/03 10:27:00 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

char	*get_key(char *env_line)
{
	int		j;
	int		key_len;
	char	*key;

	j = 0;
	while (env_line[j] && env_line[j] != '=')
		j++;
	if (j == 0)
		return (NULL);
	key_len = j;
	key = malloc(sizeof(char) * key_len + 1);
	if (!key)
		return (NULL);
	j = 0;
	while (j < key_len)
		key[j++] = env_line[j++];
	key[j] = 0;
	return (key);
}

char	*get_value(char *env_line)
{
	int		i;
	char	*equal_pos;
	char	*value;

	i = 0;
	equal_pos = ft_strchr(env_line, '=');
	if (equal_pos == 0)
		return (NULL);
	value = ft_strdup(equal_pos + 1);
	if (!value)
		return (NULL);
	return (value);
}
