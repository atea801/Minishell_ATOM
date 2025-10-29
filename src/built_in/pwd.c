/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:07:37 by aautret           #+#    #+#             */
/*   Updated: 2025/10/29 16:04:13 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Affiche ;e repertoire de travail actuel
 *
 * @param cmd
 * @return int 0 == success 1 == erreur
 */
int	builtin_pwd(t_cmd *cmd)
{
	char	buffer[BUFFER_SIZE];

	(void)cmd;
	if (pwd_parser(cmd) == 1)
	{
		return (1);
	}
	if (!getcwd(buffer, BUFFER_SIZE))
	{
		write(2, "echec de recuperation du chemin\n", 31);
		perror("pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}

int	pwd_parser(t_cmd *cmd)
{
	int count;
	int i;
	int j;

	count = 0;
	i = 1;
	j = 0;
	if (!cmd->argv[i])
		return (0);
	while (cmd->argv[i][j])
	{
		if (cmd->argv[i][j] == '-')
			count++;
		j++;
	}
	if (count >= 2)
	{
		write(2, "Atom: pwd: --: invalid option\n", 30);
		write(2, "pwd: usage: pwd [-LP]\n", 22);
		return (1);
	}
	else if (count == 1)
	{
		write(2, "Atom: pwd: ", 11);
		write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(2, ": invalid option\n", 17);
		write(2, "pwd: usage: pwd [-LP]\n", 22);
		return (1);
	}
	return (0);
}