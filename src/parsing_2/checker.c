/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:02:31 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 17:13:16 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"


int	parse_redir_alone(t_token **token_2)
{
	t_token	*t_head_2;

	t_head_2 = *token_2;
	if (!t_head_2 || !t_head_2->type || !t_head_2->next)
		return (0);
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0
			|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0))
		&& t_head_2->next == NULL)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
		t_head_2 = t_head_2->next;
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0)
		|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0))
		return (1);
	return (0);
}
