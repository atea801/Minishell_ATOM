/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:38:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 10:08:53 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:38:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/05 18:05:34 by aautret          ###   ########.fr       */
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

char	**env_list_to_tab(t_atom_env *env_list)
{
	t_atom_env	*start;
	char		**tab;
	int			count;
	int			key_len;
	int			value_len;
	int			i;
	int			j;
	int			k;
	int			x;

	start = env_list;
	i = 0;
	count = count_var_env(env_list);
	// alloue le nombre de boite necessaire mais n'alloue pas le
	// contenu de la boite
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	
	// allouer le contenu de la boite
	env_list = start;
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
			// Libère la mémoire déjà allouée
			x = 0;
			while (x < i)
			{
				free(tab[x]);
				x++;
			}
			free(tab);
			return (NULL);
		}
		i++;
		env_list = env_list->next;
	}
	// remplir le contenu de la boite
	env_list = start;
	i = 0;
	while (env_list && i < count)
	{
		j = 0;
		if (env_list->key)
		{
			while (env_list->key[j])
			{
				tab[i][j] = env_list->key[j];
				j++;
			}
		}
		tab[i][j++] = '=';
		if (env_list->has_value && env_list->value)
		{
			k = 0;
			while (env_list->value[k])
			{
				tab[i][j++] = env_list->value[k++];
			}
		}
		tab[i][j] = '\0';
		i++;
		env_list = env_list->next;
	}
	tab[i] = NULL;
	return (tab);
}

// char	**env_list_to_tab(t_atom_env *env_list)
// {
// 	t_atom_env	*start;
// 	char		**tab;
// 	int			count;
// 	int			key_len;
// 	int			value_len;
// 	int			i;
// 	int			j;
// 	int			k;
// 	int			x;

// 	start = env_list;
// 	i = 0;
// 	// alloue le nombre de boite necessaire mais n'alloue pas le contenu de la boite
// 	count = count_var_env(env_list);
// 	tab = malloc(sizeof(char *) * (count + 1));
// 	if (!tab)
// 	return (NULL);

// 	// allouer le contenu de la boite
// 	env_list = start;
// 	i = 0;
// 	while (env_list && i < count)
// 	{
// 		if (env_list->key)
// 			key_len = ft_strlen(env_list->key);
// 		else
// 			key_len = 0;
// 		if (env_list->has_value && env_list->value)
// 			value_len = ft_strlen(env_list->value);
// 		else
// 			value_len = 0;
// 		tab[i] = malloc(sizeof(char) * (key_len + value_len + 2));
// 		if (!tab[i])
// 		{
// 			// Libère la mémoire déjà allouée
// 			x = 0;
// 			while (x < i)
// 			{
// 				free(tab[x]);
// 				x++;
// 			}
// 			free(tab);
// 			return (NULL);
// 		}
// 		i++;
// 		env_list = env_list->next;
// 	}
// 	// remplir le contenu de la boite
// 	env_list = start;
// 	i = 0;
// 	while (env_list && i < count)
// 	{
// 		j = 0;
// 		if (env_list->key)
// 		{
// 			while (env_list->key[j])
// 			{
// 				tab[i][j] = env_list->key[j];
// 				j++;
// 			}
// 		}
// 		tab[i][j++] = '=';
// 		if (env_list->has_value && env_list->value)
// 		{
// 			k = 0;
// 			while (env_list->value[k])
// 			{
// 				tab[i][j++] = env_list->value[k++];
// 			}
// 		}
// 		tab[i][j] = '\0';
// 		i++;
// 		env_list = env_list->next;
// 	}
// 	tab[i] = NULL;
// 	return (tab);
// }