/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:34:48 by aautret           #+#    #+#             */
/*   Updated: 2025/09/25 10:56:28 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_token_list(t_token *head)
{
	while (head && head->value)
	{
		printf("value: %s | type: %s\n", head->value, head->type);
		head = head->next;
	}
}


void	print_token_list_type(t_token *head)
{
	while (head && head->value)
	{
		printf("%s ", head->type);
		head = head->next;
	}
	printf("\n");
}

int	check_error(char *res)
{
	int	i;
	int	count_in;
	int	count_out;

	i = -1;
	count_in = 0;
	count_out = 0;
	while (res[++i])
		if (res[i] == '<')
			count_in++;
	i = -1;
	while (res[++i])
		if (res[i] == '>')
			count_out++;
	if (count_in > 0 && count_out > 0)
		return (0);
	if (count_in > 0)
		return (count_in);
	return (count_out);
}

void	print_error(char *res)
{
	if (check_error(res) == 4)
		printf("bash: syntax error near unexpected token `%c'", res[0]);
	else if ((check_error(res) == 5)
		|| (check_error(res) >= 5 && res[0] == '>'))
		printf("bash: syntax error near unexpected token `%c%c'",
			res[0], res[1]);
	else if (check_error(res) >= 6 && res[0] == '<')
		printf("bash: syntax error near unexpected token `%c%c%c'", res[0],
			res[1], res[2]);
}
