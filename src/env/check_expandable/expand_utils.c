/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:10:20 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/05 20:21:55 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	expand_all_tokens(t_minishell *shell, t_token_2 *head)
{
	t_token_2	*current;

	current = head;
	while (current)
	{
		if (current->is_expand == 1 && current->value)
			expand_all_vars(shell, current);
		current = current->next;
	}
}

char	*replace_env_var(t_minishell *shell, char *s)
{
	char	*tmp;

	if (s[0] == '$')
	{
		tmp = s;
		if (s[1] == '?' && s[2] == 0)
			s = ft_itoa(shell->exit_code);
		else if (search_in_list(&shell->env, s))
			s = ft_strdup(search_in_list(&shell->env, s));
		else
			s = ft_strdup("");
		if (!s)
			return (free(tmp), shell->exit_code = 12, NULL);
		free(tmp);
	}
	return (s);
}


void	check_expendable(char *res, t_token_2 *token_2)
{
	int		index;
	char	*pos;

	index = 0;
	while (token_2 && token_2->value)
	{
		if (res)
			pos = ft_strnstr(res + index, token_2->value, ft_strlen(res));
		if (pos && token_2->value[0] == '$' && (token_2->value[1] == '?' 
			|| ft_isalnum(token_2->value[1]) || token_2->value[1] == '_'))
		{
			index = pos - res;
			if ((!in_single_quote(res, index) && !in_double_quote(res, index))
				|| (in_double_quote(res, index) && !in_single_quote(res,
						index)))
				token_2->is_expand = 1;
			else if (in_single_quote(res, index))
				token_2->is_expand = 0;
			else
				token_2->is_expand = 0;
		}
		token_2 = token_2->next;
	}
}

int	in_single_quote(char *res, int pos)
{
	int	in_single;
	int	i;

	in_single = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == '\'')
			in_single = !in_single;
		i++;
	}
	return (in_single);
}

int	in_double_quote(char *res, int pos)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == '\"')
			in_double = !in_double;
		i++;
	}
	return (in_double);
}
