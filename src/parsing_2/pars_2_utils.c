/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:42:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/23 10:28:47 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Compte de nombre de commande
 * 
 * @param token_head 
 * @return int 
 */
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

void	print_token_2_list(t_token_2 *token_2)
{
	t_token_2	*t_head_2;

	t_head_2 = token_2;
	while (t_head_2)
	{
		if (t_head_2->value)
			printf("TOKEN 2 = value:%s | type:%s\n", t_head_2->value, t_head_2->type);
		t_head_2 = t_head_2->next;
	}
}

void	print_token_2_list_type(t_token_2 *token_2)
{
	t_token_2	*t_head_2;

	t_head_2 = token_2;
	printf("T_TOKEN_2 :");
	while (t_head_2 && t_head_2->value)
	{
		printf("%s ", t_head_2->type);
		t_head_2 = t_head_2->next;
	}
	printf("\n");
}

// void	print_cmd_list(t_cmd *cmd_list)
// {
// 	int	i;

// 	while (cmd_list)
// 	{
// 		printf("cmd: %s | ac: %d\n", cmd_list->cmd, cmd_list->ac);
// 		if (cmd_list->args)
// 		{
// 			i = 0;
// 			while (cmd_list->args[i])
// 			{
// 				printf("  arg[%d]: %s\n", i, cmd_list->args[i]);
// 				i++;
// 			}
// 		}
// 		cmd_list = cmd_list->next;
// 	}
// }
