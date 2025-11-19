/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:47:58 by codespace         #+#    #+#             */
/*   Updated: 2025/11/19 13:13:21 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Assigne la structure d'environnement et la rempli au fur et a mesure
 *
 * @param env
 * @param env_line
 */
void	put_key_and_value(t_atom_env **env, char *env_line, int islast)
{
	(*env)->key = get_key(env_line);
	(*env)->value = get_value(env_line);
	if (ft_strchr(env_line, '='))
		(*env)->has_value = true;
	else
		(*env)->has_value = false;
	if (!islast)
	{
		(*env)->next = malloc(sizeof(t_atom_env));
		(*env)->next->next = NULL;
		(*env)->next->key = NULL;
		(*env)->next->value = NULL;
		(*env)->next->has_value = false;
		(*env)->next->has_twin = false;
		(*env)->next->size = 0;
		*env = (*env)->next;
	}
}

/**
 * @brief Fonction principale qui recupere et creer la copie de
 * l'environnement dans notre liste chainee,
 * ligne par ligne
 *
 * @param my_env
 * @param env
 */
void	my_getenv(t_atom_env **my_env, char **env)
{
	int			i;
	int			count;
	t_atom_env	*iter;

	i = 0;
	count = 0;
	iter = *my_env;
	while (env[count])
		count++;
	while (i < count)
	{
		put_key_and_value(&iter, env[i], i == count - 1);
		i++;
	}
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
