/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_check_valide.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:12:52 by aautret           #+#    #+#             */
/*   Updated: 2025/11/08 14:19:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Vérifie si une redirection est seule dans la liste de tokens.
 *
 * - Détecte si "REDIR_IN" "REDIR_OUT" sans argument
 *
 * - Retourne 1 si une redirection est seule (erreur de syntaxe), 0 sinon.
 *
 * @param token_2
 * @return int
 */
int	parse_redir_alone(t_token **token_2)
{
	t_token	*t_head_2;

	t_head_2 = *token_2;
	if (!t_head_2 || !t_head_2->type || !t_head_2->next)
		return (0);
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0
			|| ft_strcmp(t_head_2->type, "REDIR_OUT") == 0
			|| ft_strcmp(t_head_2->type, "HEREDOC") == 0
			|| ft_strcmp(t_head_2->type, "APPEND") == 0)
		&& t_head_2->next == NULL)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
		t_head_2 = t_head_2->next;
	if ((ft_strcmp(t_head_2->type, "REDIR_IN") == 0)
		|| (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0)
		|| (ft_strcmp(t_head_2->type, "HEREDOC") == 0)
		|| (ft_strcmp(t_head_2->type, "APPEND") == 0))
		return (1);
	return (0);
}

/**
 * @brief Détecte si la liste commence ou finit par un pipe,
 * ou si deux pipes se suivent, ce qui indique une erreur de syntaxe.
 *
 * @param token_2
 * @return char *
 */
char	*check_pipe(t_token *token_2)
{
	t_token	*current;

	if (!token_2 || !token_2->type)
		return (NULL);
	if (ft_strcmp(token_2->type, "PIPE") == 0)
		return (token_2->value);
	current = token_2;
	while (current && current->type)
	{
		if (ft_strcmp(current->type, "PIPE") == 0 && current->next
			&& current->next->type && ft_strcmp(current->next->type,
				"PIPE") == 0)
			return ("|");
		if (!current->next)
			break ;
		current = current->next;
	}
	if (current && current->type && ft_strcmp(current->type, "PIPE") == 0)
		return (current->value);
	return (NULL);
}

/**
 * @brief Vérifie la présence d'erreurs dans la liste de tokens.
 *

	* Parcourt la liste de tokens et retourne 1 si un token possède le type "ERROR".
 * Sinon, retourne 0.
 *
 * @param token_head
 * @return char *
 */
t_token	*check_error(t_token *token_head)
{
	t_token	*t_head_1;

	t_head_1 = token_head;
	while (t_head_1 && t_head_1->type)
	{
		if (ft_strcmp(t_head_1->type, "ERROR") == 0)
			return (t_head_1);
		t_head_1 = t_head_1->next;
	}
	return (NULL);
}

int	check_redir(t_token **token_head)
{
	t_token	*error_token;

	if (!token_head || !*token_head)
		return (0);
	error_token = check_error(*token_head);
	if (!error_token)
		return (0);
	if (!error_token->value || error_token->value[0] == '\0')
		return (0);
	if (ft_strchr(error_token->value, '<') || ft_strchr(error_token->value,
			'>'))
	{
		print_redir_error(&error_token);
		return (1);
	}
	return (0);
}

int	check_all(t_minishell *shell, t_token **token_head)
{
	char	*pf;

	if (!token_head || !*token_head)
		return (0);
	pf = check_pipe(*token_head);
	if (pf)
	{
		printf("Minishell: syntax error near unexpected token `%s'\n", pf);
		shell->exit_code = 2;
		return (1);
	}
	// Vérifier d'abord les erreurs de redirection malformées (><, <>, etc.)
	if (check_redir(token_head))
	{
		shell->exit_code = 2;
		return (1);
	}
	// Ensuite vérifier les redirections seules (sans argument)
	if (parse_redir_alone(token_head))
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}
