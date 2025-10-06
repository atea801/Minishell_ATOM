/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:42:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/06 10:19:21 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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
