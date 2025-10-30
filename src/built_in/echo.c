/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:05:59 by aautret           #+#    #+#             */
/*   Updated: 2025/10/30 16:24:58 by aautret          ###   ########.fr       */
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
	if (echo_parser(cmd) > 1)
	{
		flag = 1;
		i = echo_parser(cmd);
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

int	echo_parser(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->argv[i] && cmd->argv[i][0] == '-')
	{
		j = 1;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] != 0)
			return (i);
		i++;
	}
	return (1);
}

int	echo_completed(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	while (cmd)
	{
		builtin_echo(cmd);
		cmd = cmd->next;
	}
	return (0);
}
