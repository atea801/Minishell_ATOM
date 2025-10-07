/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/07 13:51:38 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	parsing_2(t_token *token_head, t_token_2 *token_2)
{
	t_token_2	*print;
	t_token_2	*t_head_2;
	t_token		*token_print;

	token_print = token_head;
	t_head_2 = token_2;
	printf("nbr = %d\n", count_cmd(token_print));
	print = get_input_pos(&token_head, &t_head_2);
	return ;
}
