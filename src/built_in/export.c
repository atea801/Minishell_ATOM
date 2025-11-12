/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:06:05 by aautret           #+#    #+#             */
/*   Updated: 2025/11/12 16:34:16 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

// parsing de variables 


// get key -> passer le parser
//      si invlaide status 1 not a valid identifier

// si = present -> creer et mettre a jour la variable/value et marque exporte
//      sinon marque exportee sans changer la valeur


static int	check_args_export(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (1);
	i = 1;
	if (str[0] == '_' || ft_isalpha((unsigned char)str[0]))
	{
		while (str[i])
		{
			if (ft_isalnum((unsigned char)str[i]) || str[i] == '_')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	builtin_export(t_minishell *shell)
{
	if (shell->cmd->argv[1] && check_args_export(shell->cmd->argv[1]) == 0)
	{
		valide_key(&shell->env, shell->cmd->argv[1]);
		printf("Success add\n");
		shell->should_exit = 0;
	}
	else
	{
		printf("Nothing exported\n");
		shell->should_exit = 1;
		return (1);
	}
	return (0);
}

