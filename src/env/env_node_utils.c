/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:59:39 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 11:01:03 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	init_new_node_env_free(t_atom_env *new_node)
{
	free(new_node->key);
	free(new_node->value);
	free(new_node);
}
