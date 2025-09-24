/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:07 by aautret           #+#    #+#             */
/*   Updated: 2025/09/24 18:24:58 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Determine si le type du token est un MOT
 *
 * exemples :
 *
 *- accepte echo file.txt -l -w grep ...
 *
 * @param res
 * @return char*
 */
char	*type_mot(char *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if ((res[i] >= 'a' && res[i] <= 'z') || (res[i] >= '0' && res[i] <= '9')
			|| (res[i] >= 'A' && res[i] <= 'Z') || res[i] == '-')
			return ("MOT");
		i++;
	}
	return (NULL);
}

/**
 * @brief Dertermine si le type du token est un PIPE
 *
 * @param res
 * @return char*
 */
char	*type_pipe(char *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '|')
			return ("PIPE");
		i++;
	}
	return (NULL);
}

/**
 * @brief Dertermine si le type du token est une REDIRECTION IN
 * ou REDIRECTION OUT
 *
 * @param res
 * @return char*
 */
char	*type_redir(char *res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '<' && res[i + 1] == 32)
			return ("REDIR_IN");
		if (res[i] == '>')
			return ("REDIR_OUT");
		i++;
	}
	return (NULL);
}

/**
 * @brief Dertermine si le type du token est un HEREDOC
 *
 * @param res
 * @return char*
 */
char	*type_heredoc(char *res)
{
	if (res[0] == '<' && res[1] == '<' && res[2] == '\0')
		return ("HEREDOC");
	return (NULL);
}

/**
 * @brief Détermine le type du token en appelant successivement
 * les fonctions de type (heredoc, redir, pipe, mot)
 *
 * @param res
 * @return char* (nom du type ou NULL si inconnu)
 */
char	*get_token_type(char *res)
{
	char	*type;

	type = type_heredoc(res);
	if (type)
		return (type);
	type = type_redir(res);
	if (type)
		return (type);
	type = type_pipe(res);
	if (type)
		return (type);
	type = type_mot(res);
	if (type)
		return (type);
	return (NULL);
}
