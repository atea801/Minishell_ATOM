/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:02:06 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 10:18:24 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	count_var_env(t_atom_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

void	free_allocated_tab(char **tab, int i)
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

void	fill_up_box_tabs(t_atom_env *env_list, char **tab, int count)
{
	int i;
	int j;
	int k;

	i = 0;
	while (env_list && i < count)
	{
		j = 0;
		while (env_list->key && env_list->key[j])
		{
			tab[i][j] = env_list->key[j];
			j++;
		}
		tab[i][j++] = '=';
		if (env_list->has_value && env_list->value)
		{
			k = 0;
			while (env_list->value[k])
				tab[i][j++] = env_list->value[k++];
		}
		tab[i][j] = '\0';
		i++;
		env_list = env_list->next;
	}
	tab[i] = NULL;
}

char	**env_list_to_tab_new(t_atom_env *env_list)
{
	return (env_list_to_tab(env_list));
}
