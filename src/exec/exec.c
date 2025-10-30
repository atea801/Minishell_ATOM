/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:44:26 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/30 11:18:35 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile)
		redirect_input(cmd->infile);
	if (cmd->outfile)
	{
		if (cmd->append == 1)
			redirect_append(cmd->outfile);
		else
			redirect_output(cmd->outfile);
	}
}

void	exec_single_cmd(t_minishell *shell, t_cmd *cmd, char **tab_to_env)
{
	(void)tab_to_env;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;

	// Pour l'instant, on teste uniquement les built-ins
	if (is_builtin(cmd->argv[0]) == 1)
	{
		shell->exit_code = execute_builtin(shell);
		return ;
	}

	// Pour l'instant, on affiche juste un message pour les commandes externes
	printf("Command '%s' is not a built-in (external commands not implemented yet)\n",
		cmd->argv[0]);
	shell->exit_code = 127;
}