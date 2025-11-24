/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:35:15 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 12:56:57 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Initialise HOME et OLDPWD et recuperant le home depuis l'environnement
 *
 * Fonction utilitaire de builtin_cd
 * @param shell
 * @param home
 * @param oldpwd
 * @return int
 */
int	cd_init_vars(t_minishell *shell, char **home, char **oldpwd)
{
	*home = search_in_list(&shell->env, "HOME");
	*oldpwd = getcwd(NULL, 0);
	if (!*home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (!*oldpwd)
	{
		perror("Minishell: getcwd");
		return (1);
	}
	return (0);
}

/**
 * @brief Dispatch la logique de cd selon le nombre d'arguments
 * (argc) et la valeur de l'argument
 *
 * - gestion de cd sans args
 *
 * - gestion de cd -
 *
 * - gestion de cd ~
 *
 * - gestion de cd (avec "" + "    ") partie en commentaire
 *
 *
 * // // Vérifier si l'argument est vide ou ne contient que des espaces
 * // if (!shell->cmd->argv[1] || shell->cmd->argv[1][0] == '\0')
 * // {
 * // ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
 * // 	free(oldpwd);
 * // 	return (1);
 * // }
 * // // Vérifier si l'argument ne contient que des espaces
 * // i = 0;
 * // while (shell->cmd->argv[1][i] && (shell->cmd->argv[1][i] == ' '
 * // 		|| shell->cmd->argv[1][i] == '\t'
 * // 		|| shell->cmd->argv[1][i] == '\n'
 * // 		|| shell->cmd->argv[1][i] == '\r'
 * // 		|| shell->cmd->argv[1][i] == '\v'
 * // 		|| shell->cmd->argv[1][i] == '\f'))
 * // 	i++;
 * @param shell
 * @param home
 * @param oldpwd
 * @param new_pwd
 * @return int 0 = succes / 1 = erreur
 */
int	cd_dispatch_case(t_minishell *shell, char *home, char *oldpwd,
		char *new_pwd)
{
	int	i;

	i = 0;
	if (shell->cmd->argc == 1)
		return (case_cd_sin_arg(shell, home, oldpwd, new_pwd));
	if (shell->cmd->argc == 2)
	{
		if (!shell->cmd->argv[1][i])
		{
			ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
			return (free(oldpwd), 1);
		}
		if (ft_strcmp(shell->cmd->argv[1], "-") == 0)
			return (cd_special_case_dash(shell, oldpwd, new_pwd));
		if (ft_strcmp(shell->cmd->argv[1], "~") == 0)
			return (case_cd_sin_arg(shell, home, oldpwd, new_pwd));
		return (cd_with_args(shell, oldpwd, new_pwd));
	}
	if (shell->cmd->argc > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (free(oldpwd), 1);
	}
	return (0);
}

/**
 * @brief Parcourt une liste de tokens et détecte si
 * un token ayant type égal à "ERROR" existe.
 *
 * - Utile pour décider d'ignorer l'exécution de certains
 * builtins si parsing invalide. Dans le code builtin_cd il est
 * commenté mais conservé comme utilitaire.
 * @param tok1
 * @return int
 */
int	has_parsing_errors(t_token *tok1)
{
	t_token	*current;

	if (!tok1)
		return (0);
	current = tok1;
	while (current)
	{
		if (current->type && ft_strcmp(current->type, "ERROR") == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Point d'entrée du built-in cd. Ordonne la validation et
 * exécution du changement de répertoire.
 *
 * - builtin_cd délègue toute la logique au dispatch
 * @param shell
 * @return int
 */
int	builtin_cd(t_minishell *shell)
{
	char	*home;
	char	*oldpwd;
	char	new_pwd[BUFFER_SIZE];

	if (!shell->should_execute)
	{
		ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
		return (1);
	}
	if (cd_init_vars(shell, &home, &oldpwd) == 1)
		return (1);
	return (cd_dispatch_case(shell, home, oldpwd, new_pwd));
}
