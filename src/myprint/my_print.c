/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:54:37 by aautret           #+#    #+#             */
/*   Updated: 2025/10/23 12:57:23 by aautret          ###   ########.fr       */
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
	printf("T_TOKEN :");
	while (head && head->value)
	{
		printf("%s ", head->type);
		head = head->next;
	}
	printf("\n");
}

void	print_cmd_list(t_cmd *cmd)
{
	int node;
	int i;

	node = 0;
	while (cmd)
	{
		printf("\nCOMMANDE %d\n", node);
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				printf("argv[%d] : %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		if (cmd->infile)
			printf("infile : %s\n", cmd->infile);
		if (cmd->outfile)
			printf("outfile : %s\n", cmd->outfile);
		printf("HEREDOC : %d\n", cmd->here_doc);
		printf("APPEND : %d\n", cmd->append);
		cmd = cmd->next;
		node++;
	}
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

void	print_env_tab(char **tab_env)
{
	int	i;

	i = 0;
	if (!tab_env)
		return ;
	while (tab_env[i])
	{
		printf("tab_env[%d]: %s\n", i, tab_env[i]);
		i++;
	}
}