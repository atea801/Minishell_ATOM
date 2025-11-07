/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:35:15 by aautret           #+#    #+#             */
/*   Updated: 2025/11/07 15:29:47 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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

int	cd_dispatch_case(t_minishell *shell, char *home, char *oldpwd,
		char *new_pwd)
{
	int	i;
	
	if (shell->cmd->argc == 1)
		return (case_cd_sin_arg(shell, home, oldpwd, new_pwd));
	if (shell->cmd->argc == 2)
	{
		// Vérifier si l'argument est vide ou ne contient que des espaces
		if (!shell->cmd->argv[1] || shell->cmd->argv[1][0] == '\0')
		{
			ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
			free(oldpwd);
			return (1);
		}
		
		// Vérifier si l'argument ne contient que des espaces
		i = 0;
		while (shell->cmd->argv[1][i] && (shell->cmd->argv[1][i] == ' ' || 
			shell->cmd->argv[1][i] == '\t' || shell->cmd->argv[1][i] == '\n' ||
			shell->cmd->argv[1][i] == '\r' || shell->cmd->argv[1][i] == '\v' ||
			shell->cmd->argv[1][i] == '\f'))
			i++;
		if (!shell->cmd->argv[1][i])
		{
			ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
			free(oldpwd);
			return (1);
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
		free(oldpwd);
		return (1);
	}
	return (0);
}

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

int	is_empty_string_error(t_token *tok1)
{
	t_token	*current;

	if (!tok1)
		return (0);
	current = tok1;
	while (current)
	{
		if (current->type && ft_strcmp(current->type, "ERROR") == 0)
		{
			// Si c'est une erreur avec une valeur vide, c'est cd ""
			if (!current->value || current->value[0] == '\0')
				return (0); // cd "" ne doit pas afficher d'erreur
			// Si c'est une erreur avec des espaces, c'est cd "   "
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	builtin_cd(t_minishell *shell)
{
	char	*home;
	char	*oldpwd;
	char	new_pwd[BUFFER_SIZE];

	// Vérifier s'il y a des erreurs de parsing pour cd "   " (espaces)
	if (shell->cmd->argc == 1 && is_empty_string_error(shell->tok1))
	{
		ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
		return (1);
	}

	// cd "" reste silencieux et ne fait rien (comme bash)
	if (shell->cmd->argc == 1 && has_parsing_errors(shell->tok1))
	{
		return (0); // Retour 0 (succès) et reste dans le même répertoire
	}

	// Si le parsing a échoué (ex: cd ""), ne pas exécuter
	if (!shell->should_execute)
	{
		ft_putstr_fd("Minishell: cd: invalid argument\n", 2);
		return (1);
	}

	if (cd_init_vars(shell, &home, &oldpwd) == 1)
		return (1);
	return (cd_dispatch_case(shell, home, oldpwd, new_pwd));
}
