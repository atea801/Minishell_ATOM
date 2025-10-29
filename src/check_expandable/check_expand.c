/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:27:38 by aautret           #+#    #+#             */
/*   Updated: 2025/10/29 16:43:18 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	var_len(char *s, int start)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (ft_isalnum(s[start + i]) || s[start + i] == '_')
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	free(s2);
	return (res);
}

static char	*process_variable(t_minishell *shell, char *s, int *i, char *res)
{
	char	*before;
	int		len;

	before = ft_substr(s, 0, *i);
	res = ft_strjoin_free(res, before);
	if (!res)
		return (NULL);
	len = 1 + var_len(s, *i + 1);
	if (s[*i + 1] == '?')
		len = 2;
	before = ft_substr(s, *i, len);
	if (!before)
		return (free(res), NULL);
	res = ft_strjoin_free(res, replace_env_var(shell, before));
	return (res);
}

static char	*handle_dollar(t_minishell *shell, char **s, int *i, char *res)
{
	int	len;

	len = 1 + var_len(*s, *i + 1);
	if ((*s)[*i + 1] == '?')
		len = 2;
	res = process_variable(shell, *s, i, res);
	if (!res)
		return (NULL);
	*s += *i + len;
	*i = 0;
	return (res);
}

void	expand_all_vars(t_minishell *shell, t_token_2 *token)
{
	char	*res;
	char	*s;
	int		i;

	res = ft_strdup("");
	if (!res)
		return ;
	s = token->value;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			res = handle_dollar(shell, &s, &i, res);
			if (!res)
				return (free(token->value), (void)0);
		}
		else
			i++;
	}
	if (*s)
		res = ft_strjoin_free(res, ft_strdup(s));
	free(token->value);
	token->value = res;
}
