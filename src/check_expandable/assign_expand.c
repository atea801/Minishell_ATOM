/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:45:18 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/23 11:24:25 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	assign_expand(t_minishell *shell, t_token_2 *token_2)
{
	while (token_2 && token_2->is_expand)
	{
		if (token_2->is_expand == 1)
		{
			expander(shell, token_2);
		}
		token_2 = token_2->next;
	}
}

int	expander(t_minishell *shell, t_token_2 *token_2)
{
	char	*key;
	char	*expanded;

	if (!token_2 || !token_2->value)
		return (0);
	if (ft_strcmp(token_2->value, "$?") == 0)
	{
		expanded = ft_itoa(shell->exit_code);
		if (!expanded)
			return (0);
		free(token_2->value);
		token_2->value = expanded;
		return (1);
	}
	key = get_key(token_2->value);
	if (!key)
		return (0);
	expanded = search_in_list(&shell->env, key);
	free(key);
	if (expanded)
	{
		free(token_2->value);
		token_2->value = ft_strdup(expanded);
	}
	return (1);
}
