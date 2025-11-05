/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:31:39 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/31 11:19:29 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	count_var_env(t_atom_env *env_list)
{
	t_atom_env	*current;
	int			count;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**create_box_tab_env(int count)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i <= count)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

void	free_for_env_list_to_tab(char **tab, int i)
{
	int	x;

	x = 0;
	while (x < i)
	{
		free(tab[x]);
		x++;
	}
	free(tab);
}

int	allocate_content_box_tabs(t_atom_env *env_list, char **tab, int count)
{
	int	i;
	int	key_len;
	int	value_len;

	i = 0;
	while (env_list && i < count)
	{
		if (env_list->key)
			key_len = ft_strlen(env_list->key);
		else
			key_len = 0;
		if (env_list->has_value && env_list->value)
			value_len = ft_strlen(env_list->value);
		else
			value_len = 0;
		tab[i] = malloc(sizeof(char) * (key_len + value_len + 2));
		if (!tab[i])
		{
			free_for_env_list_to_tab(tab, i);
			return (-1);
		}
		i++;
		env_list = env_list->next;
	}
	return (0);
}
