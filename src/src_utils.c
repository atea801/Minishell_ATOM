/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:35:16 by aautret           #+#    #+#             */
/*   Updated: 2025/10/03 17:07:03 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_all(t_token *token_head, t_atom_env *env_head)
{
	free_token_list(token_head);
	free_env_list(env_head);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		// if (head->type)
		// 	free(head->type);
		free(head);
		head = tmp;
	}
}

void	free_env_list(t_atom_env *head)
{
	t_atom_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		if (head->key)
			free(head->key);
		free(head);
		head = tmp;
	}
}
