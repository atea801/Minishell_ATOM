/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:55:29 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/04 13:47:47 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_env_list(t_atom_env *env_head)
{
	while (env_head && env_head->value)
	{
		printf("KEY = %s | VALUE = %s\n", env_head->key, env_head->value);
		env_head = env_head->next;
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

void	print_cmd_list(t_cmd *cmd)
{
	int	node;
	int	i;

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
	printf("\nTOKEN 2 :\n");
	while (t_head_2)
	{
		if (t_head_2->value)
			printf("value:%s | type:%s | isexpand:%d\n", t_head_2->value,
				t_head_2->type, token_2->is_expand);
		t_head_2 = t_head_2->next;
	}
}
