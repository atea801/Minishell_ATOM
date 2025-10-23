/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:48:02 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/23 18:20:07 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	free_token_1_only(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		if (head->value)
		{
			free(head->value);
			head->value = NULL;
		}
		free(head);
		head = tmp;
	}
}

void	free_token_2_list(t_token_2 **t_head_2)
{
	t_token_2	*head_2;
	t_token_2	*tmp_2;

	if (!t_head_2 || !*t_head_2)
		return ;
	head_2 = *t_head_2;
	while (head_2)
	{
		tmp_2 = head_2->next;
		if (head_2->value)
			free(head_2->value);
		free(head_2);
		head_2 = tmp_2;
	}
	*t_head_2 = NULL;
}
