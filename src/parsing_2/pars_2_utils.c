/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:42:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/05 14:54:55 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	count_cmd(t_token *token_head)
{
	int	count;

	count = 0;
	while(token_head)
	{
		if (token_head->type)
			count++;
		token_head = token_head->next;
	}
	return (count);
}