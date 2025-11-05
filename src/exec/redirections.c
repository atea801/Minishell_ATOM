/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:59:50 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 14:25:09 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	check_all_redirections(t_token_2 *token_2)
{
	t_token_2	*current;
	t_token_2	*prev;

	if (!token_2)
		return ;
	current = token_2;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->type, "INFILE") == 0)
			prev = current;
		current = current->next;
	}
}
