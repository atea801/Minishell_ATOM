/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:59:50 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/24 11:11:22 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	check_all_redirections(t_token_2 *token_2)
{
	t_token_2	*current;

	if (!token_2)
		return ;
	current = token_2;
	while (current)
	{
		if (ft_strcmp(current->type, "INFILE") == 0)
			current = current->next;
	}
}

void	fd_close_safe(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
