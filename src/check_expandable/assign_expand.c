/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:45:18 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/17 17:22:19 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	assign_expand(t_token_2 *token_2, t_atom_env **env)
{
	t_token_2	*t_head_2;

	t_head_2 = token_2;
	while (t_head_2 && t_head_2->value)
	{
		if (t_head_2->is_expand == 1 && t_head_2->value[0] == '$')
		{
			expander(t_head_2, env);
		}
		t_head_2 = t_head_2->next;
	}
}

int	expander(t_token_2 *token_2, t_atom_env **env)
{
	t_token_2	*t_head_2;
	t_atom_env	*env_head;
	char		*str;

	env_head = *env;
	t_head_2 = token_2;
	str = t_head_2->value;
	str++;
	while (env_head && t_head_2->value && env_head->key)
	{
		if (ft_strcmp(str, env_head->key) == 0)
		{
			free(t_head_2->value);
			t_head_2->value = ft_strdup(env_head->value);
			return (0);
		}
		env_head = env_head->next;
	}
	free(t_head_2->value);
	t_head_2->value = ft_strdup("");
	return (1);
}
