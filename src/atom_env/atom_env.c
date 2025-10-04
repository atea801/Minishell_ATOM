/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:47:58 by codespace         #+#    #+#             */
/*   Updated: 2025/10/03 17:17:47 by aautret          ###   ########.fr       */
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
	{
		key[j] = env_line[j];
		j++;
	}
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

void	put_key_and_value(t_atom_env **env, char *env_line)
{
	(*env)->key = get_key(env_line);
	(*env)->value = get_value(env_line);
	(*env)->next = malloc(sizeof(t_atom_env));
	if (!(*env)->next)
		return ;
	(*env) = (*env)->next;
	(*env)->next = NULL;
	(*env)->key = NULL;
	(*env)->value = NULL;
	(*env)->has_value = false;
	(*env)->has_twin = false;
	(*env)->size = 0;
}

void	my_getenv(t_atom_env **my_env, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		put_key_and_value(my_env, env[i]);
}

// int	check_special_case(char *env_line)
// {
// 	int		i;
// 	char	*equal_pos;

// 	i = -1;
// 	if (env_line[0] == '=')
// 		return (1);
// 	equal_pos = ft_strchr(env_line, '=');
// 	if (ft_strchr(equal_pos + 1, '='))
// 		return (2);
// 	while (env_line[++i])
// 	{
// 		if (env_line[i] == '=')
// 			if (env_line[i + 2] != 0)
// 				return (3);
// 	}
// 	return (0);
// }
