/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:42:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/23 12:58:16 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Compte de nombre de commande
 * 
 * @param token_head 
 * @return int 
 */
int	count_cmd(t_token *token_head)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token_head;
	while (current)
	{
		if (current->type)
			count++;
		current = current->next;
	}
	return (count);
}


