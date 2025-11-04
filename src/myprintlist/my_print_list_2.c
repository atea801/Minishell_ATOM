/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_list_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:00:03 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/04 13:48:23 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_token_list(t_token *head)
{
	while (head && head->value)
	{
		printf("value:%s | type:%s\n", head->value, head->type);
		head = head->next;
	}
}


void	print_token_list_type(t_token *head)
{
	printf("\nT_TOKEN :");
	while (head && head->value)
	{
		printf("%s ", head->type);
		head = head->next;
	}
	printf("\n");
}