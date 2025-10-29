/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:44:26 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/29 13:59:32 by aautret          ###   ########.fr       */
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
	pid_t	pid;
	int		status;

	// Si c'est un builtin, l'exécuter directement (pas de fork)
	if (is_builtin(cmd->argv[0]) == 1)
	{
		shell->exit_code = execute_builtin(cmd);
		return ;
	}
	// Sinon, fork pour exécuter une commande externe
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		shell->exit_code = 1;
		return ;
	}
	if (pid == 0) // Processus enfant
	{
		// Gérer les redirections A FAIREEEEEEEEE
		handle_redirections(cmd);
		// Exécuter la commande
		execve()
		// Si execve échoue
		perror(cmd->argv[0]);
		exit(127);
	}
	// Processus parent : attendre la fin du child
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
}
