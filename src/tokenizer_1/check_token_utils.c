/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:27:14 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 16:43:06 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	check_two_chars(char *value)
{
	if (value[0] == '>' && value[1] == '<')
		return (1);
	if (value[0] == '<' && value[1] == '>')
		return (3);
	return (0);
}

int	check_three_chars(char *value)
{
	if (value[0] == '<' && value[1] == '>' && value[2] == '<')
		return (1);
	if (value[0] == '<' && value[1] == '>' && value[2] == '>')
		return (3);
	return (0);
}

int	check_many_chars(char *value, size_t len)
{
	if ((value[0] == '<' && value[1] == '>')
		|| (value[0] == '>' && value[1] == '<'))
	{
		if (value[len - 1] == '<')
			return (2);
		if (value[len - 1] == '>')
			return (4);
	}
	return (0);
}
