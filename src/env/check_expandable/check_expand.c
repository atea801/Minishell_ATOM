/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:27:38 by aautret           #+#    #+#             */
/*   Updated: 2025/11/21 14:02:35 by tlorette         ###   ########.fr       */
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

static char	*handle_escaped_dollar(char **s, int *i, char *res)
{
	char	*before;

	before = ft_substr(*s, 0, *i);
	res = ft_strjoin_free(res, before);
	if (!res)
		return (NULL);
	res = ft_strjoin_free(res, ft_strdup("$"));
	if (!res)
		return (NULL);
	*s += *i + 2;
	*i = 0;
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

static char	*expand_vars_loop(t_minishell *shell, char *s, char *res)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] == '$')
			res = handle_escaped_dollar(&s, &i, res);
		else if (s[i] == '$')
			res = handle_dollar(shell, &s, &i, res);
		else
			i++;
		if (!res)
			return (NULL);
	}
	if (*s)
		res = ft_strjoin_free(res, ft_strdup(s));
	return (res);
}

/**
 * @brief
 *
 * @param shell
 * @param token
 * @note rajout du dernier if Permet de restaurer placeholders utilisees
 * pour proteger les '$' provenant de quotes simple lors de la tokenisation
 */
void	expand_all_vars(t_minishell *shell, t_token_2 *token)
{
	char	*res;
	int		k;

	if (ft_strcmp(token->type, "HEREDOC") == 0)
		return ;
	res = expand_vars_loop(shell, token->value, ft_strdup(""));
	if (!res)
		return (free(token->value), (void)0);
	free(token->value);
	token->value = res;
	k = 0;
	while (token->value && token->value[k])
	{
		if (token->value[k] == '\x07')
			token->value[k] = '$';
		k++;
	}
}
