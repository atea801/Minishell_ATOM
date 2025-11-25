/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:14:47 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 17:19:24 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

char	*create_heredoc_op(void)
{
	char	*op;

	op = malloc(4 * sizeof(char));
	if (!op)
		return (NULL);
	op[0] = '<';
	op[1] = '<';
	op[2] = '<';
	op[3] = '\0';
	return (op);
}

char	*create_lessgreater_op(void)
{
	char	*op;

	op = malloc(3 * sizeof(char));
	if (!op)
		return (NULL);
	op[0] = '<';
	op[1] = '>';
	op[2] = '\0';
	return (op);
}

char	*create_double_op(char c)
{
	char	*op;

	op = malloc(3 * sizeof(char));
	if (!op)
		return (NULL);
	op[0] = c;
	op[1] = c;
	op[2] = '\0';
	return (op);
}

char	*create_single_op(char c)
{
	char	*op;

	op = malloc(2 * sizeof(char));
	if (!op)
		return (NULL);
	op[0] = c;
	op[1] = '\0';
	return (op);
}
