/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_cmd_node_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:38:03 by aautret           #+#    #+#             */
/*   Updated: 2025/11/05 18:38:21 by tlorette         ###   ########.fr       */
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
	int	i;

	if (!new_node)
		return ;
	if (new_node->argv)
	{
		i = 0;
		while (new_node->argv[i])
		{
			free(new_node->argv[i]);
			i++;
		}
		free(new_node->argv);
	}
	if (new_node->infile)
		free(new_node->infile);
	if (new_node->outfile)
		free(new_node->outfile);
	if (new_node->heredoc_delim)
		free(new_node->heredoc_delim);
	if (new_node->fd_in != -1)
		close(new_node->fd_in);
	if (new_node->fd_out != -1)
		close(new_node->fd_out);
	free(new_node);
}

/**
 * @brief Fonction de decoupage pour les free
 * de delete_node_list_cmd
 * 
 * @param node 
 */
void	free_delete_node_list(t_cmd *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node->heredoc_delim)
		free(node->heredoc_delim);
	if (node->fd_in != -1)
		close(node->fd_in);
	if (node->fd_out != -1)
		close(node->fd_out);
	free(node);
}
