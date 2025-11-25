/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:42:32 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/25 15:48:57 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Compte de nombre de commande
 *
 * @param token_head
 * @return int
 */
int	count_cmd(t_token *token_head)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token_head;
	while (current)
	{
		if (current->type)
			count++;
		current = current->next;
	}
	return (count);
}

int	check_access_to_file(char *type, char *file)
{
	struct stat	sb;

	if (!file)
		return (-1);
	if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putendl_fd("Error: Is a directory", 2);
		return (-1);
	}
	if (ft_strcmp(type, "INFILE") == 0)
	{
		if (access(file, F_OK) == -1 || access(file, R_OK) == -1)
			return (perror(file), -1);
	}
	else if (ft_strcmp(type, "OUTFILE") == 0)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
			return (perror(file), -1);
	}
	else if (ft_strcmp(type, "APPEND") == 0)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
			return (perror(file), -1);
	}
	return (0);
}

/**
 * @brief Ouvre un fichier selon son type et gère l'ancien fd
 *
 * @param type Type de token (INFILE, OUTFILE, APPEND)
 * @param file Nom du fichier
 * @param old_fd Pointeur vers l'ancien fd à fermer/remplacer
 * @return int Nouveau fd ou -1 en cas d'erreur
 */
int	open_redir_file(char *type, char *file, int *old_fd)
{
	int	fd;

	if (check_access_to_file(type, file) == -1)
		return (-1);
	if (ft_strcmp(type, "INFILE") == 0)
		fd = open(file, O_RDONLY);
	else if (ft_strcmp(type, "OUTFILE") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(type, "APPEND") == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
		return (-1);
	if (*old_fd != -1)
		close(*old_fd);
	*old_fd = fd;
	return (fd);
}

/**
 * @brief Parcourt les tokens et ouvre tous les fichiers de redirections
 *
 * @param tokens Liste des tokens à parcourir
 * @param fd_in Pointeur pour stocker le dernier fd d'input
 * @param fd_out Pointeur pour stocker le dernier fd d'output
 * @return int 0 si succès, -1 si erreur
 */
int	open_all_redirs_from_tokens(t_token_2 *tokens, int *fd_in, int *fd_out)
{
	t_token_2	*current;
	int			result;

	current = tokens;
	*fd_in = -1;
	*fd_out = -1;
	while (current && current->type && ft_strcmp(current->type, "PIPE") != 0)
	{
		if (ft_strcmp(current->type, "INFILE") == 0)
		{
			result = open_redir_file(current->type, current->value, fd_in);
			if (result == -1)
			{
				if (*fd_in != -1 && *fd_in != 0)
					close(*fd_in);
				if (*fd_out != -1 && *fd_out != 1)
					close(*fd_out);
				*fd_in = -1;
				*fd_out = -1;
				return (-1);
			}
		}
		else if (ft_strcmp(current->type, "OUTFILE") == 0
			|| ft_strcmp(current->type, "APPEND") == 0)
		{
			result = open_redir_file(current->type, current->value, fd_out);
			if (result == -1)
			{
				if (*fd_in != -1 && *fd_in != 0)
					close(*fd_in);
				if (*fd_out != -1 && *fd_out != 1)
					close(*fd_out);
				*fd_in = -1;
				*fd_out = -1;
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	count_args_to_pipe(t_token_2 *token_2)
{
	int			count;
	t_token_2	*t_head_2;

	count = 0;
	t_head_2 = token_2;
	while (t_head_2 && t_head_2->type && ft_strcmp(t_head_2->type, "PIPE") != 0)
	{
		if (ft_strcmp(t_head_2->type, "ARGS") == 0 || ft_strcmp(t_head_2->type,
				"CMD") == 0)
			count++;
		t_head_2 = t_head_2->next;
	}
	return (count);
}
