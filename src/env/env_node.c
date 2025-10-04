/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:18:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/04 15:44:09 by tlorette         ###   ########.fr       */
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
void	add_node_to_end(t_atom_env **env_head, char *key, char *value)
{
	t_atom_env	*new_node;
	t_atom_env	*current;

	new_node = init_new_node(key, value);
	if (!new_node)
		return ;
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

t_atom_env	*init_new_node(char *key, char *value)
{
	t_atom_env	*new_node;

	new_node = malloc(sizeof(t_atom_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->has_twin = false;
	new_node->has_value = false;
	new_node->next = NULL;
	if (value)
		new_node->size = ft_strlen(value);
	else
		new_node->size = 0;
	return (new_node);
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
	value = get_value(env_line);
	if (key)
	{
		add_node_to_end(env_head, key, value);
		free(key);
		if (value)
			free(value);
	}
	return ;
}

int	change_node_list(t_atom_env **env, char *key, char *value)
{
	t_atom_env	*current;

	if (!env || !*env)
		return (0);
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				return (0);
			return (1);
		}
		current = current->next;
	}
	add_node_to_end(env, key, value);
	return (2);
}

void	delete_node_list(t_atom_env **env, char *key)
{
	t_atom_env	*current;
	t_atom_env	*previous;

	if (!env || !*env)
		return ;
	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env = current->next;
			free(current->value);
			free(current->key);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
	return ;
}
