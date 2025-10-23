/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:05:59 by aautret           #+#    #+#             */
/*   Updated: 2025/10/23 18:13:52 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") != 0)
		return (1);
	i = 1;
	flag = 0;
	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-n") == 0)
	{
		flag = 1;
		i = 2;
	}
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

// int	check_echo_arg(t_cmd *cmd)
// {
// 	int		i;
// 	t_cmd	*cmd_head;

// 	cmd_head = cmd;
// 	i = 0;
// 	if (cmd_head->argv[1] && cmd_head->argv[1][0] == '-')
// 	{
// 		while ()
// 	}
// }
