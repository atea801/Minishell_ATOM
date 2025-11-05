/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:38:47 by aautret           #+#    #+#             */
/*   Updated: 2025/11/05 15:04:31 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	get_env_entry_len(t_atom_env *env_list)
{
	int	key_len;
	int	value_len;

	key_len = 0;
	value_len = 0;
	if (env_list->key)
		key_len = ft_strlen(env_list->key);
	if (env_list->has_value && env_list->value)
		value_len = ft_strlen(env_list->value);
	return (key_len + value_len + 2);
}

static char	**allocate_tab_boxes(t_atom_env *env_list, int count)
{
	char		**tab;
	int			i;

	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (env_list && i < count)
	{
		tab[i] = malloc(sizeof(char) * get_env_entry_len(env_list));
		if (!tab[i])
		{
			free_allocated_tab(tab, i);
			return (NULL);
		}
		i++;
		env_list = env_list->next;
	}
	return (tab);
}

static void	fill_tab_entry(char *tab_entry, t_atom_env *env_node)
{
	int	j;
	int	k;

	j = 0;
	if (env_node->key)
	{
		k = 0;
		while (env_node->key[k])
			tab_entry[j++] = env_node->key[k++];
	}
	tab_entry[j++] = '=';
	if (env_node->has_value && env_node->value)
	{
		k = 0;
		while (env_node->value[k])
			tab_entry[j++] = env_node->value[k++];
	}
	tab_entry[j] = '\0';
}

static void	fill_all_entries(char **tab, t_atom_env *env_list, int count)
{
	int	i;

	i = 0;
	while (env_list && i < count)
	{
		fill_tab_entry(tab[i], env_list);
		i++;
		env_list = env_list->next;
	}
	tab[i] = NULL;
}

char	**env_list_to_tab(t_atom_env *env_list)
{
	char	**tab;
	int		count;

	if (!env_list)
		return (NULL);
	count = count_var_env(env_list);
	tab = allocate_tab_boxes(env_list, count);
	if (!tab)
		return (NULL);
	fill_all_entries(tab, env_list, count);
	return (tab);
}
