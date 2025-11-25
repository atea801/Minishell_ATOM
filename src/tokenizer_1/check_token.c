/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:49 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/25 16:42:59 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Affiche le message d'erreur approprié pour un token de
 * redirection malformé
 *
 * Analyse la valeur du token ERROR et détermine quel
 * opérateur de redirection est en cause pour afficher le
 * bon message d'erreur.
 * Gère les cas: <<<, <<, >>, <>, <, >
 *
 * @param t_head Pointeur vers le token ERROR contenant la redirection malformée
 */
void	print_redir_error(t_token **t_head)
{
	t_token	*t_error;
	char	*val;

	if (!t_head || !*t_head || !(*t_head)->value)
		return ;
	t_error = *t_head;
	val = t_error->value;
	if (ft_strcmp(val, "<>") == 0)
		write(2, "Minishell: syntax error near unexpected token `newline'\n",
			57);
	else if (ft_strncmp(val, "<<<", 3) == 0)
		write(2, "Minishell: syntax error near unexpected token `<<<'\n", 53);
	else if (ft_strncmp(val, "<<", 2) == 0)
		write(2, "Minishell: syntax error near unexpected token `<<'\n", 52);
	else if (ft_strncmp(val, ">>", 2) == 0)
		write(2, "Minishell: syntax error near unexpected token `>>'\n", 52);
	else if (val[0] == '<')
		write(2, "Minishell: syntax error near unexpected token `<'\n", 51);
	else if (val[0] == '>')
		write(2, "Minishell: syntax error near unexpected token `>'\n", 51);
}

// void	print_redir_error(t_token **error_token)
// {
// 	if (!error_token || !*error_token)
// 		return ;
// 	if (!(*error_token)->value)
// 	{
// 		printf("Minishell: syntax error\n");
// 		return ;
// 	}
// 	printf("Minishell: syntax error near unexpected token `%s'\n",
// 		(*error_token)->value);
// }

int	check_redir_in(t_token *t_head)
{
	t_token	*redir_in_error;

	redir_in_error = t_head;
	if (!redir_in_error || !redir_in_error->type || !redir_in_error->value)
		return (0);
	if (ft_strcmp(redir_in_error->type, "ERROR") == 0
		&& ft_strlen(redir_in_error->value) == 3
		&& redir_in_error->value[2] == '<')
		return (1);
	if (ft_strcmp(redir_in_error->type, "ERROR") == 0
		&& ft_strlen(redir_in_error->value) > 3
		&& redir_in_error->value[0] == '<' && redir_in_error->value[1] == '<')
		return (2);
	return (0);
}

int	check_redir_out(t_token *t_head)
{
	t_token	*redir_out_error;

	redir_out_error = t_head;
	if (!redir_out_error || !redir_out_error->type || !redir_out_error->value)
		return (0);
	if (ft_strcmp(redir_out_error->type, "ERROR") == 0
		&& ft_strlen(redir_out_error->value) == 3
		&& redir_out_error->value[2] == '>')
		return (3);
	if (ft_strcmp(redir_out_error->type, "ERROR") == 0
		&& ft_strlen(redir_out_error->value) > 3
		&& redir_out_error->value[0] == '>' && redir_out_error->value[1] == '>')
		return (4);
	return (0);
}

int	check_redir_alone(t_token *t_head)
{
	char	*value;
	size_t	len;

	if (!t_head || !t_head->type || !t_head->value)
		return (0);
	if (ft_strcmp(t_head->type, "ERROR") != 0)
		return (0);
	value = t_head->value;
	len = ft_strlen(value);
	if (len == 2)
		return (check_two_chars(value));
	if (len == 3)
		return (check_three_chars(value));
	if (len > 3)
		return (check_many_chars(value, len));
	return (0);
}

int	check_only_redir(t_token *t_head)
{
	if (!t_head || !t_head->type)
		return (0);
	if (ft_strcmp(t_head->type, "REDIR_IN") == 0 || ft_strcmp(t_head->type,
			"REDIR_OUT") == 0)
		return (5);
	return (0);
}
