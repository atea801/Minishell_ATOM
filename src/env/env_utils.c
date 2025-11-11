/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:23:05 by aautret           #+#    #+#             */
/*   Updated: 2025/11/10 13:40:00 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Recupere la cle dans l'environnement, 
 * une cle correspond a la partie avant le "="
 * 
 * @param env_line 
 * @return char* 
 */
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

/**
 * @brief Recupere la valeur correspondante a la cle indique avant,
 * la valeur est le contenu assigne a une cle 
 * (tout ce qu'il y a apres le premier "=")
 * 
 * @param env_line 
 * @return char* 
 */
char	*get_value(char *env_line)
{
	char	*equal_pos;
	char	*value;

	equal_pos = ft_strchr(env_line, '=');
	if (equal_pos == 0)
		return (NULL);
	value = ft_strdup(equal_pos + 1);
	if (!value)
		return (NULL);
	return (value);
}

/**
 * @brief Cherche cle dans l'env par nom de variable

 * 
 * @param env 
 * @param key 
 * @return char* search_key->value
 */
char	*search_in_list(t_atom_env **env, char *key)
{
	t_atom_env	*searched_key;
	char		*k;

	if (!*env || !env || !key)
		return (NULL);
	k = key;
	if (k[0] == '$')
		k = k + 1;
	searched_key = *env;
	while (searched_key)
	{
		if (searched_key->key && ft_strcmp(searched_key->key, k) == 0)
			return (searched_key->value);
		searched_key = searched_key->next;
	}
	return (NULL);
}

