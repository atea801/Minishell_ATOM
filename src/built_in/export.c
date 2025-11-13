/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:06:05 by aautret           #+#    #+#             */
/*   Updated: 2025/11/13 14:52:14 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static void	export_update_var_found(t_atom_env *current, char *value)
{
	if (current->value)
		free(current->value);
	if (value)
	{
		current->value = ft_strdup(value);
		current->has_value = true;
	}
	else
	{
		current->value = NULL;
		current->has_value = false;
	}
	current->has_twin = true;
}

static int	search_in_env_export(t_atom_env *current, char *value, char *key)
{
	if (current->key)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			export_update_var_found(current, value);
			free(key);
			if (value)
				free(value);
			return (1);
		}
	}
	return (0);
}

static void	valide_key_updated(t_atom_env **env_head, char *env_line)
{
	char		*key;
	char		*value;
	t_atom_env	*current;

	key = get_key(env_line);
	value = get_value(env_line);
	if (!key)
		return ;
	current = *env_head;
	while (current)
	{
		if (search_in_env_export(current, value, key) == 1)
			return ;
		current = current->next;
	}
	add_node_to_end(env_head, key, value);
	current = *env_head;
	while (current->next)
		current = current->next;
	current->has_twin = true;
	if (value)
		current->has_value = true;
	free(key);
	if (value)
		free(value);
}

static int	check_args_export(char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0])
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_export(t_minishell *shell)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (shell->cmd->argc > 1 && shell->cmd->argv[i])
	{
		if (check_args_export(shell->cmd->argv[i]) == 0)
		{
			valide_key_updated(&shell->env, shell->cmd->argv[i]);
		}
		else
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(shell->cmd->argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		i++;
	}
	shell->should_exit = 0;
	return (ret);
}
