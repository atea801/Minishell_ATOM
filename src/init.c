/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:00:00 by aautret           #+#    #+#             */
/*   Updated: 2025/11/18 14:02:59 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Initialise seulement une structure t_token (sans t_token_2)
 * 
 * @param token_head Pointeur vers le head de la liste de tokens
 * @return int 0 si succès, 1 si erreur
 * @note Initialisation quote_type
 */
int	init_token_1_only(t_token **token_head)
{
	*token_head = malloc(sizeof(t_token));
	if (!*token_head)
		return (1);
	(*token_head)->value = NULL;
	(*token_head)->type = NULL;
	(*token_head)->quote_type = 0;
	(*token_head)->next = NULL;
	return (0);
}

/**
 * @brief Initialise une structure t_token
 * 
 * @param token_head Pointeur vers le head de la liste de tokens
 * @return int 0 si succès, 1 si erreur
 * @note Initialisation quote_type
 */
int	init_token_struct(t_token **token_head, t_token_2 **token_2)
{
	*token_head = malloc(sizeof(t_token));
	if (!*token_head)
		return (1);
	(*token_head)->value = NULL;
	(*token_head)->type = NULL;
	(*token_head)->quote_type = 0;
	(*token_head)->next = NULL;
	*token_2 = malloc(sizeof(t_token_2));
	if (!*token_2)
		return (1);
	(*token_2)->value = NULL;
	(*token_2)->type = NULL;
	(*token_2)->is_expand = 1;
	(*token_2)->next = NULL;
	return (0);
}


/**
 * @brief Initialise une structure t_atom_env
 * 
 * @param env_head Pointeur vers le head de la liste d'environnement
 * @return int 0 si succès, 1 si erreur
 */
int	init_env_struct(t_atom_env **env_head)
{
	*env_head = malloc(sizeof(t_atom_env));
	if (!*env_head)
		return (1);
	(*env_head)->key = NULL;
	(*env_head)->value = NULL;
	(*env_head)->next = NULL;
	(*env_head)->has_value = false;
	(*env_head)->has_twin = false;
	(*env_head)->size = 0;
	return (0);
}

/**
 * @brief Initialise une structure t_cmd
 * 
 * @param env_head Pointeur vers le head de la liste des commandes
 * @return int 0 si succès, 1 si erreur
 */
int	init_cmd_struct(t_cmd **cmd_list)
{
	*cmd_list = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd_list)
		return (1);
	return (0);
}

/**
 * @brief initalisation principale, avec appels sous fonctions pour 
 * initialiser la structure de l'environnement et la structure du token
 * 
 * 
 * POSSIBILITE D'AFFICHER L'ENVIRONNEMENT ICI = FONCTION A DECOMMENTER
 * 
 * @param env_head 
 * @param token_head 
 * @param env 
 */
void	init_all(t_atom_env **env_head, t_token **token_head,
	char **env, t_token_2 **token_2)
{
	t_atom_env	*env_struct;

	if (init_token_struct(token_head, token_2) != 0)
		return ;
	if (init_env_struct(env_head) != 0)
	{
		free(*token_head);
		return ;
	}
	// if (init_cmd_struct(cmd_list) != 0)
	// 	return ;
	env_struct = *env_head;
	my_getenv(env_head, env);
	*env_head = env_struct;
	// print_env_list(*env_head);
}
