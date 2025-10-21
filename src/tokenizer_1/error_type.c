/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:48:57 by aautret           #+#    #+#             */
/*   Updated: 2025/10/21 11:29:34 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Assigne le type ERREUR si il n'y a pas de type 
 * qui a ete alloue precedement 
 * 
 * @param t_head 
 */
void	set_token_error(t_token **t_head)
{
	t_token	*error;

	error = *t_head;
	while (error->next)
	{
		if (!error->type)
		{
			error->type = "ERROR";
			return ;
		}
		error = error->next;
	}
}