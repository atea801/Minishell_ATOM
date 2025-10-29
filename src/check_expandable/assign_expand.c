// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   assign_expand.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/17 11:45:18 by tlorette          #+#    #+#             */
// /*   Updated: 2025/10/28 18:15:08 by tlorette         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "atom.h"

// void	assign_expand(t_minishell *shell, t_token_2 *token_2)
// {
// 	while (token_2 && token_2->is_expand)
// 	{
// 		if (token_2->is_expand == 1)
// 		{
// 			expander(shell, token_2);
// 		}
// 		token_2 = token_2->next;
// 	}
// }

// int	special_expand(t_minishell *shell, t_token_2 *token_2)
// {
// 	char	*expanded;

// 	expanded = NULL;
// 	if (ft_strcmp(token_2->value, "$?") == 0)
// 	{
// 		expanded = ft_itoa(shell->exit_code);
// 		if (!expanded)
// 			return (0);
// 		free(token_2->value);
// 		token_2->value = expanded;
// 		return (1);
// 	}
// 	return (0);
// }

// int	get_expand(t_cmd *cmd)
// {
// 	int		j;
// 	int		i;
// 	int		key_len;
// 	char	*key;

// 	j = 0;
// 	i = 0;
// 	while (cmd->argv[i])
// 	{
// 		if (cmd->argv[i][0] == '$')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// char	*multiple_expand(t_minishell *shell, t_cmd *cmd)
// {
// 	int		i;
// 	int		j;
// 	char	*key;
// 	char	*res;
// 	int		key_len;

// 	i = get_expand(cmd);
// 	j = 0;
// 	while (cmd->argv[i][++j])
// 	{
// 		if (cmd->argv[i][j] == '$')
// 		{
// 			key_len = j;
// 			key = malloc(sizeof(char) * j + 1);
// 			j = 0;
// 			while (j < key_len)
// 			{
// 				key[j] = cmd->argv[i][j];
// 				j++;
// 			}
// 			res = ft_strdup(search_in_list(&shell->env, key));
// 			free(key);
// 		}
// 	}
// 	return (res);
// }

// int	expander(t_minishell *shell, t_cmd *cmd)
// {
// 	char	*key;
// 	char	*expanded;
// 	int		i;

// 	if (!cmd || !cmd->argv)
// 		return (0);
// 	if (special_expand(shell, cmd) == 1)
// 		return (1);
// 	i = 0;
// 	// key = get_key(token_2->value);
// 	// if (!key)
// 	// 	return (0);
// 	expanded = search_in_list(&shell->env, key);
// 	free(key);
// 	if (expanded)
// 	{
// 		free(cmd->argv[i]);
// 		cmd->argv[i] = ft_strdup(expanded);
// 	}
// 	return (1);
// }
