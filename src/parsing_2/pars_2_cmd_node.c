/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:18:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 13:40:39 by aautret          ###   ########.fr       */
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
void	add_node_to_end_cmd(t_cmd **cmd_head, char *cmd, char *args)
{
	t_cmd	*new_node;
	t_cmd	*current;

	new_node = init_new_node_cmd(cmd, args);
	if (!new_node)
		return ;
	if (!*cmd_head)
	{
		*cmd_head = new_node;
		return ;
	}
	current = *cmd_head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/**
 * @brief Creation d'un nouveau noeud
 * 
 * @param key 
 * @param value 
 * @return t_cmd* new node
 */
t_cmd	*init_new_node_cmd(char *cmd, char *args)
{
	t_cmd	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	new_node->args[i++] = ft_strdup(args);
	if (!new_node->cmd || !new_node->args)
	{
		free_init_new_node_cmd(new_node);
		return (NULL);
	}
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = NULL;
	new_node->here_doc = NULL;
	new_node->next = NULL;
	if (args)
		new_node->ac = ft_strlen(args);
	else
		new_node->ac = 0;
	return (new_node);
}


/**
 * @brief Ajoute ou modifie une variable
 * 
 * Si elle existe : libérer l'ancienne valeur et assigner la nouvelle
 * 
 * Si elle n'existe pas : créer un nouveau nœud et l'ajouter à la liste
 * 
 * @param env 
 * @param key 
 * @param value 
 * @return int 
 * 0 = erreur malloc
 * 
 * 1 = modification
 * 
 * 2 = ajout en fin de lsite
 */
int	change_node_list_cmd(t_cmd **cmd_list, char *cmd, char *args)
{
	t_cmd	*current;
	int		i;
	
	i = 0;
	if (!cmd_list || !*cmd_list)
	return (0);
	current = *cmd_list;
	while (current)
	{
		if (ft_strcmp(current->cmd, cmd) == 0)
		{
			free(current->args);
			current->args[i++] = ft_strdup(args);
			if (!current->args)
			return (0);
			return (1);
		}
		current = current->next;
	}
	add_node_to_end_cmd(cmd_list, cmd, args);
	return (2);
}

/**
 * @brief Fonction de suppression de variable
 * 
 * Rechercher la variable dans la liste
 * 
 * @param env 
 * @param key 
 */
void	delete_node_list_cmd(t_cmd **cmd_list, char *cmd)
{
	t_cmd	*current;
	t_cmd	*previous;
	
	if (!cmd_list || !*cmd_list)
	return ;
	current = *cmd_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->cmd, cmd) == 0)
		{
			if (previous)
			previous->next = current->next;
			else
			*cmd_list = current->next;
			free_delete_node_list(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
	return ;
}

/**
 * @brief Prend une chaine de caractere et verifie que la cle est valide
 * (qu'elle existe)
 * si la cle est valide on ajoute le nouveau noeud
 *
 * @param env_head
 * @param env_line
 */
// void	valide_cmd(t_cmd **cmd_head, char *input)
// {
// 	char	*cmd;
// 	char	*args;

// 	cmd = get_cmd(input);//A FAIRE
// 	args = get_args(input); // A FAIRE
// 	if (cmd)
// 	{
// 		add_node_to_end(cmd_head, cmd, args);
// 		free(cmd);
// 		if (args)
// 			free(args);
// 	}
// 	return ;
// }
