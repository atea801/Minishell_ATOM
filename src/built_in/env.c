/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:41:03 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 17:33:42 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Permet d'afficher l'env mais uniquement les cles
 * associe a une value
 * 
 * @param shell 
 * @return int 
 */
int	builtin_env(t_minishell *shell)
{
	t_atom_env	*tmp;

	tmp = shell->env;
	if (shell->cmd->argv[1])
	{
		write(2, "Atom: env:", 10);
		write(2, shell->cmd->argv[1], ft_strlen(shell->cmd->argv[1]));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if (shell->env == NULL)
		return (0);
	while (tmp)
	{
		if (tmp->has_value == true && tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
