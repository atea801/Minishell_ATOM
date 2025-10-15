/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:18:47 by aautret           #+#    #+#             */
/*   Updated: 2025/10/15 11:52:58 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Permet d'ajouter un noeud a la fin de la liste chainee
 *
 * @param cmd_head
 * @param argv
 */
void	add_node_to_end_cmd(t_cmd **cmd_head, char **argv)
{
	t_cmd	*new_node;
	t_cmd	*current;

	new_node = init_new_node_cmd(argv);
	if (!new_node)
		return ;
	if (!*cmd_head)
	{
		*cmd_head = new_node;
		return ;
	}
	current = *cmd_head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

/**
 * @brief Creation d'un nouveau noeud
 * 
 * @param argv 
 * @return t_cmd* new node
 */
t_cmd	*init_new_node_cmd(char **argv)
{
	t_cmd	*new_node;
	int		i;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	i = 0;
	if (argv)
	{
		while (argv[i])
			i++;
	}
	new_node->argc = i;
	new_node->argv = malloc(sizeof(char *) * (i + 1));
	if (!new_node->argv)
	{
		free(new_node);
		return (NULL);
	}
	i = 0;
	if (argv)
	{
		while (argv[i])
		{
			new_node->argv[i] = ft_strdup(argv[i]);
			if (!new_node->argv[i])
			{
				free_init_new_node_cmd(new_node);
				return (NULL);
			}
			i++;
		}
	}
	new_node->argv[i] = NULL;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->heredoc_delim = NULL;
	new_node->append = 0;
	new_node->here_doc = 0;
	new_node->next = NULL;
	return (new_node);
}


/**
 * @brief Ajoute un argument a une commande existante
 * 
 * @param cmd 
 * @param arg 
 * @return int 0 = erreur, 1 = succès
 */
int	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_argv;
	int		i;

	if (!cmd || !arg)
		return (0);
	new_argv = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!new_argv)
		return (0);
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(arg);
	if (!new_argv[i])
	{
		free(new_argv);
		return (0);
	}
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc++;
	return (1);
}

/**
 * @brief Fonction de suppression de la liste de commandes
 * 
 * @param cmd_list 
 */
void	delete_node_list_cmd(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		free_delete_node_list(current);
		current = next;
	}
	*cmd_list = NULL;
}

/**
 * @brief Configure les redirections d'une commande
 * 
 * @param cmd 
 * @param type "REDIR_IN", "REDIR_OUT", "HEREDOC", "APPEND"
 * @param file 
 */
void	set_cmd_redirection(t_cmd *cmd, char *type, char *file)
{
	if (!cmd || !type || !file)
		return ;
	if (ft_strcmp(type, "REDIR_IN") == 0)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(file);
	}
	else if (ft_strcmp(type, "REDIR_OUT") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(file);
		cmd->append = 0;
	}
	else if (ft_strcmp(type, "APPEND") == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(file);
		cmd->append = 1;
	}
	else if (ft_strcmp(type, "HEREDOC") == 0)
	{
		if (cmd->heredoc_delim)
			free(cmd->heredoc_delim);
		cmd->heredoc_delim = ft_strdup(file);
		cmd->here_doc = 1;
	}
}
