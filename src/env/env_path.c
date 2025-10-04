/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:51:19 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/04 16:10:46 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Creation mini environnement impermeable au -i env
 * 
 * @param env 
 */
void	create_minimal_env(t_atom_env **env)
{
	char	*cwd;
	char	*username;
	char	*path_home;

	cwd = getcwd(NULL, 0);
	username = get_username(cwd);
	path_home = get_home(cwd);
	add_node_to_end(env, "USER", username);
	add_node_to_end(env, "HOME", path_home);
	add_node_to_end(env, "PATH", "/usr/bin:/bin:/usr/local/bin");
	add_node_to_end(env, "OLDPWD", "");
	add_node_to_end(env, "PWD", cwd);
	free(cwd);
	free(username);
	free(path_home);
}

/**
 * @brief Permet de recuperer le path home
 * 
 * @param cwd 
 * @return char* /home/username
 */
char	*get_home(char *cwd)
{
	int		i;
	int		count_slash;

	count_slash = 0;
	i = 0;
	while (cwd[i])
	{
		if (cwd[i] == '/')
			count_slash++;
		if (count_slash == 3)
			return (ft_substr(cwd, 0, i));
		i++;
	}
	return (NULL);
}

/**
 * @brief Permet de recuperer le username
 * 
 * @param cwd 
 * @return char* username
 */
char	*get_username(char *cwd)
{
	int	i;

	i = 6;
	while (cwd[i])
	{
		if (cwd[i] == '/')
			return (ft_substr(cwd, 6, i - 6));
		i++;
	}
	return (NULL);
}


