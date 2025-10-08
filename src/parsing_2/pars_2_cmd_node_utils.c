/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_cmd_node_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:38:03 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 13:44:03 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Fonction de decoupage pour les free 
 * de init_new_node_cmd
 * 
 * @param new_node 
 */
void	free_init_new_node_cmd(t_cmd *new_node)
{
	free(new_node->cmd);
	free(new_node->args);
	free(new_node);
}

/**
 * @brief Fonction de decoupage pour les free
 * de delette_node_list_cmd
 * 
 * @param node 
 */
void	free_delete_node_list(t_cmd *node)
{
	free(node->args);
	free(node->cmd);
	free(node->infile);
	free(node->outfile);
	free(node->append);
	free(node->here_doc);
	free(node);
}
