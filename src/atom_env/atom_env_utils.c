/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:23:05 by aautret           #+#    #+#             */
/*   Updated: 2025/10/03 16:13:22 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_env_list(t_atom_env *env_head)
{
	while (env_head && env_head->value)
	{
		printf("KEY = %s | VALUE = %s\n", env_head->key, env_head->value);
		env_head = env_head->next;
	}
}

