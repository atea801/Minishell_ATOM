/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:02:06 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 10:08:49 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	fill_up_box_tabs(t_atom_env *env_list, char **tab, int count)
{
	int i;
	int j;
	int k;

	i = 0;
	while (env_list && i < count)
	{
		j = 0; // IMPORTANT : réinitialiser j pour chaque ligne
		// Copier la clé
		while (env_list->key && env_list->key[j])
		{
			tab[i][j] = env_list->key[j];
			j++;
		}
		// Ajouter le '='
		tab[i][j++] = '=';
		// Copier la valeur si elle existe
		if (env_list->has_value && env_list->value)
		{
			k = 0;
			while (env_list->value[k])
				tab[i][j++] = env_list->value[k++];
		}
		// Terminer la chaîne
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