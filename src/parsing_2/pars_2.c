/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 14:04:56 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	parsing_2(t_token *token_head, t_token_2 *token_2)
{
	t_token_2	*t_head_2;
	t_token		*t_head_1;

	t_head_1 = token_head;
	t_head_2 = token_2;
	tokenizer_2(t_head_1, t_head_2);
	if (check_all(&t_head_2) > 0)
		return (1);
	return (0);
}
