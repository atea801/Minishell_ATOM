/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom_env_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:18:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/03 18:34:36 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Permet d'ajouter un noeud a la fin de la liste chainee, 
 * sert dans le cas ou on utilise export car on va venir en rajouter un nouveau
 * 
 * @param env_head 
 * @param key 
 * @param value 
 */
void	add_env_to_end(t_atom_env **env_head, char *key, char *value)
{
	t_atom_env	*new_node;
	t_atom_env	*current;

	new_node = malloc(sizeof(t_atom_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->has_twin = false;
	new_node->has_value = false;
	new_node->next = NULL;
	if (value)
		new_node->size = ft_strlen(value);
	else
		new_node->size = 0;
	if (!*env_head)
	{
		*env_head = new_node;
		return ;
	}
	current = *env_head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/**
 * @brief Prend une chaine de caractere et verifie que la cle est valide 
 * (qu'elle existe)
 * si la cle est valide on ajoute le nouveau noeud 
 * 
 * @param env_head 
 * @param env_line 
 */
void	valide_key(t_atom_env **env_head, char *env_line)
{
	char	*key;
	char	*value;

	key = get_key(env_line);
	value = get_value(env_head);
	if (key)
	{
		add_env_to_end(env_head, key, value);
		free(key);
		if (value)
			free(value);
	}
	return ;
}
