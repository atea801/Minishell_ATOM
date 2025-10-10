/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:49 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/10 18:54:24 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_redir_error(t_token **t_head)
{
	t_token	*t_error;

	t_error = *t_head;
	while (t_error)
	{
		if (check_redir_in(t_error) == 1 || check_redir_alone(t_error) == 1)
			write(2, "ATOM : syntax error near unexpected token `<'\n", 47);
		else if (check_redir_in(t_error) == 2
			|| check_redir_alone(t_error) == 2)
			write(2, "ATOM : syntax error near unexpected token `<<'\n", 48);
		else if (check_redir_alone(t_error) == 3
			|| check_redir_out(t_error) == 3)
			write(2, "ATOM : syntax error near unexpected token `>'\n", 47);
		else if (check_redir_out(t_error) == 4
			|| check_redir_alone(t_error) == 4)
			write(2, "ATOM : syntax error near unexpected token `>>'\n", 48);
		else if (check_redir_alone(t_error) == 5
			|| check_only_redir(t_error) == 5)
			write(2, "ATOM : syntax error near unexpected token `newline'\n",
				53);
		t_error = t_error->next;
	}
}

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
	t_token	*r_alone;

	r_alone = t_head;
	if (!r_alone || !r_alone->type || !r_alone->value)
		return (0);
	if (ft_strcmp(r_alone->type, "ERROR") == 0)
	{
		if (ft_strlen(r_alone->value) == 2)
		{
			if (r_alone->value[0] == '>' && r_alone->value[1] == '<')
				return (1);
			else if (r_alone->value[0] == '<' && r_alone->value[1] == '>')
				return (3);
		}
		else if (ft_strlen(r_alone->value) == 3)
		{
			if (r_alone->value[0] == '<' && r_alone->value[1] == '>'
				&& r_alone->value[2] == '<')
				return (1);
			else if (r_alone->value[0] == '<' && r_alone->value[1] == '>'
				&& r_alone->value[2] == '>')
				return (3);
		}
		else if (ft_strlen(r_alone->value) > 3)
		{
			if ((r_alone->value[0] == '<' && r_alone->value[1] == '>')
				|| (r_alone->value[0] == '>' && r_alone->value[1] == '<'))
			{
				if (r_alone->value[ft_strlen(r_alone->value) - 1] == '<')
					return (2);
				else if (r_alone->value[ft_strlen(r_alone->value) - 1] == '>')
					return (4);
			}
		}
	}
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
