/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:06:04 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/06 19:02:14 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

char	*malloc_cmd(char *str)
{
	int		count;
	char	*cmd;

	count = ft_strlen(str);
	cmd = malloc(sizeof(char) * count + 1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*copy_token_value(char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = malloc_cmd(str);
	while (str[i])
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = 0;
	return (cmd);
}

t_token_2	*get_input_pos(t_token **token_1, t_token_2 **token_2)
{
	t_token_2	*token_head_2;
	t_token		*token_head_1;
	t_token_2	*prev;

	token_head_1 = *token_1;
	token_head_2 = *token_2;
	prev = NULL;
	if (!token_head_1)
		return (NULL);
	while (token_head_1)
	{
		if (!token_head_2->next)
		{
			token_head_2->next = malloc(sizeof(t_token_2));
			if (!token_head_2->next)
				break ;
			token_head_2->next->value = NULL;
			token_head_2->next->type = NULL;
			token_head_2->next->next = NULL;
		}
		fill_cmd_or_args(&token_head_1, &token_head_2);
		fill_redirin_redirout(&token_head_1, &token_head_2);
		prev = token_head_2;
		token_head_2 = token_head_2->next;
		token_head_1 = token_head_1->next;
	}
	return (token_head_2);
}
