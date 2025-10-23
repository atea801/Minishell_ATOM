/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:05:59 by aautret           #+#    #+#             */
/*   Updated: 2025/10/23 15:54:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	//verif structure existe
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	// check echo
	if (ft_strcmp(cmd->argv[0], "echo") != 0)
		return (1);
	// test argv[1]
	i = 1;
	flag = 0;
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		flag = 1;
		i = 2;
	}
	// espace seulment si il y a un mot suivant
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}

// void	echo_limits(t_cmd *cmd)
// {
// 	if (ft_strcmp(cmd->argv[i], "\"\"") == 0 )
// }