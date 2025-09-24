/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:34:48 by aautret           #+#    #+#             */
/*   Updated: 2025/09/24 16:48:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_token_list(t_token *head)
{
	while (head && head->value)
	{
		printf("value: %s | type: %s\n", head->value, head->type);
		head = head->next;
	}
}


void	print_token_list_type(t_token *head)
{
	while (head && head->value)
	{
		printf("%s ", head->type);
		head = head->next;
	}
	printf("\n");
}
