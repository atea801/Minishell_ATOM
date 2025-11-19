/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:18:07 by aautret           #+#    #+#             */
/*   Updated: 2025/11/19 16:02:13 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Determine si le type du token est un MOT
 *
 * exemples :
 *
 *- accepte echo file.txt -l -w grep ...

 if ((res[i] >= 'a' && res[i] <= 'z') || (res[i] >= '0' && res[i] <= '9')
			|| (res[i] >= 'A' && res[i] <= 'Z') || res[i] == '-'
			|| res[i] == '.' || res[i] == ':' || res[i] == '/' || res[i] == '_'
			|| res[i] == '~' || res[i] == '\'' || res[i] == '"' || res[i] == '$'
			|| res[i] == '=' || res[i] == '+' || res[i] == '@' || res[i] == '%'
			|| res[i] == ',' || res[i] == '(' || res[i] == ')')
 *
 * @param res
 * @return char*
 */
char	*type_mot(char *res)
{
	int	i;

	i = -1;
	if (!res || !res[0])
		return (NULL);
	while (res[++i])
	{
		if ((res[i] >= 'a' && res[i] <= 'z') || (res[i] >= '0' && res[i] <= '9')
			|| (res[i] >= 'A' && res[i] <= 'Z') || res[i] == '-'
			|| res[i] == '.' || res[i] == ':' || res[i] == '/' || res[i] == '_'
			|| res[i] == '~' || res[i] == '\'' || res[i] == '"' || res[i] == '$'
			|| res[i] == '=' || res[i] == '+' || res[i] == '@' || res[i] == '%'
			|| res[i] == ',' || res[i] == '(' || res[i] == ')')
			return ("MOT");
	}
	return (NULL);
}

/**
 * @brief Dertermine si le type du token est un PIPE
 *
 * Ne gere pas les double pipe (||)
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
		if (res[i] == '|' && res[i + 1] == 0)
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
	int	count;

	i = 0;
	count = 0;
	while (res[i])
	{
		if (res[0] == '<' && res[1] == 0)
			count++;
		if (res[0] == '>' && res[1] == 0)
			count++;
		i++;
	}
	if (count == 1 && res[0] == '<')
		return ("REDIR_IN");
	if (count == 1 && res[0] == '>')
		return ("REDIR_OUT");
	return (NULL);
}

/**
 * @brief Dertermine si le type du token est un HEREDOC ou APPEND
 *
 * @param res
 * @return char*
 */
char	*type_heredoc(char *res)
{
	if (res[0] == '<' && res[1] == '<' && res[2] == '\0')
		return ("HEREDOC");
	if (res[0] == '>' && res[1] == '>' && res[2] == '\0')
		return ("APPEND");
	return (NULL);
}

/**
 * @brief Détermine le type du token en appelant successivement
 * les fonctions de type (expand, redir, pipe, mot)
 *
 * @param res
 * @return char* (nom du type ou NULL si inconnu)
 */
char	*get_token_type(char *res)
{
	char	*type;

	// Vérifier d'abord les expansions spéciales ($?)
	type = type_expand(res);
	if (type)
		return (type);
	type = type_redir(res);
	if (type)
		return (type);
	type = type_heredoc(res);
	if (type)
		return (type);
	type = type_pipe(res);
	if (type)
		return (type);
	type = type_mot(res);
	if (type)
		return (type);
	// if (!type)
	// 	print_error(res);
	return (NULL);
}
