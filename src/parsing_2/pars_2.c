/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:55:34 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 17:22:45 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Détecte si la liste commence ou finit par un pipe,
 * ou si deux pipes se suivent, ce qui indique une erreur de syntaxe.
 *
 * @param token_2
 * @return int
 */
int	check_pipe(t_token *token_2)
{
	t_token	*t_head_2;

	t_head_2 = token_2;
	if (!t_head_2 || !t_head_2->type)
		return (0);
	if (ft_strcmp(t_head_2->type, "PIPE") == 0)
		return (1);
	while (t_head_2->next && t_head_2->next->type)
	{
		if (ft_strcmp(t_head_2->type, "PIPE") == 0
			&& ft_strcmp(t_head_2->next->type, "PIPE") == 0)
			return (1);
		t_head_2 = t_head_2->next;
	}
	if (ft_strcmp(t_head_2->type, "PIPE") == 0)
		return (1);
	return (0);
}

int	check_error(t_token *token_head)
{
	t_token	*t_head_1;

	t_head_1 = token_head;
	while (t_head_1 && t_head_1->type)
	{
		if (ft_strcmp(t_head_1->type, "ERROR") == 0)
			return (1);
		t_head_1 = t_head_1->next;
	}
	return (0);
}

/**
 * @brief Vérifie la validité globale de la liste de tokens.
 *
 * - Appelle les différents checkers pour valider la syntaxe des tokens
 * @param token_2
 * @return int
 */
int	check_all(t_token **token_head)
{
	t_token	*t_head_1;

	if (!token_head || !*token_head)
		return (0);
	t_head_1 = *token_head;
	if (check_pipe(t_head_1) > 0)
		return (1);
	else if ((parse_redir_alone(&t_head_1) > 0))
		return (1);
	else if (check_error(t_head_1) > 0)
		return (1);
	return (0);
}

int	parsing_2(t_token *token_head, t_token_2 *token_2)
{
	t_token_2	*t_head_2;
	t_token		*t_head_1;
	int			error;

	t_head_1 = token_head;
	t_head_2 = token_2;
	error = check_all(&t_head_1);
	if (error > 0)
		return (1);
	else if (error == 0)
		tokenizer_2(t_head_1, t_head_2);
	return (0);
}

int	in_single_quote(char *res, int pos)
{
	int	in_single;
	int	i;

	in_single = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == 39)
			in_single = !in_single;
		i++;
	}
	return (in_single);
}

int	in_double_quote(char *res, int pos)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (res[i] == 34)
			in_double = !in_double;
		i++;
	}
	return (in_double);
}

void	check_expendable(char *res, t_token_2 *token_2)
{
	int		in_double;
	int		in_single;
	int		index;
	char	*pos;

	while (token_2 && token_2->value)
	{
		pos = ft_strnstr(res, token_2->value, ft_strlen(res));
		if (pos && token_2->value[0] == '$')
		{
			index = pos - res;
			in_single = in_single_quote(res, index);
			in_double = in_double_quote(res, index);
			if ((!in_single && !in_double) || (in_double && !in_single))
				token_2->is_expand = 1;
			else
				token_2->is_expand = 0;
		}
		else
			token_2->is_expand = 0;
		printf("is_expand = %d\n", token_2->is_expand);
		token_2 = token_2->next;
	}
}
