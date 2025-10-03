/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:47:58 by codespace         #+#    #+#             */
/*   Updated: 2025/10/03 18:15:42 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Assigne la structure d'environnement et la rempli au fur et a mesure
 * 
 * @param env 
 * @param env_line 
 */
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
