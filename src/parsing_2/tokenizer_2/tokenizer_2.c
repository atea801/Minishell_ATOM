/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:54:05 by aautret           #+#    #+#             */
/*   Updated: 2025/11/04 14:17:36 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Parcourt la liste des tokens et met à jour leur type
 * dans la structure token_2
 *
 * - utilise get_pos pour analyser chaque token +
 *  mettre à jour la structure token_2
 *
 * - Distingue les CMD, ARGS, REDIR_INT, REDIR_OUT
 * selon le type de chaque token.
 *
 * @param token_1
 * @param token_2
 */
void	get_input_pos(t_token **token_1, t_token_2 **token_2)
{
	t_token_2	*token_head_2;
	t_token		*token_head_1;
	int			first_word;

	token_head_1 = *token_1;
	token_head_2 = *token_2;
	first_word = 0;
	if (!token_head_1)
		return ;
	while (token_head_1 && token_head_1->type)
	{
		first_word = get_pos(token_head_1, token_head_2, first_word);
		token_head_2 = token_head_2->next;
		token_head_1 = token_head_1->next;
	}
}

/**
 * @brief Defini si le type est un INFILE ou un OUTFILE
 * en fonction de la redirection trouvee
 *
 * @param token_2
 * @return t_token_2
 */
void	set_infile_outfile(t_token_2 **token_2)
{
	t_token_2	*t_head_2;

	t_head_2 = *token_2;
	while (t_head_2 && t_head_2->type && t_head_2->next && t_head_2->next->type)
	{
		if (ft_strcmp(t_head_2->type, "REDIR_IN") == 0
			&& ft_strcmp(t_head_2->next->type, "CMD") == 0)
			t_head_2->next->type = "INFILE";
		if (ft_strcmp(t_head_2->type, "REDIR_OUT") == 0
			&& ft_strcmp(t_head_2->next->type, "CMD") == 0)
			t_head_2->next->type = "OUTFILE";
		t_head_2 = t_head_2->next;
	}
}

void	set_heredoc_delim(t_token_2 **token_2)
{
	t_token_2	*t_head_2;

	t_head_2 = *token_2;
	while (t_head_2 && t_head_2->next)
	{
		if (t_head_2->type && t_head_2->next->type 
			&& ft_strcmp(t_head_2->type, "HEREDOC") == 0
			&& ft_strcmp(t_head_2->next->type, "CMD") == 0)
			t_head_2->next->type = "HEREDOC_DELIM";
		t_head_2 = t_head_2->next;
	}
	return ;
}

/**
 * @brief Analyse la liste des tokens et initialise la structure token_2.
 *
 * - Détermine le type CMD ARGS REDIR_INT REDIR_OUT PIPE APPEND HEREDOC
 *
 * - Determine les OUTFILE et INFILE fonction des redirections.
 * @param token_head
 * @param token_2
 */
void	tokenizer_2(t_token *token_head, t_token_2 *token_2)
{
	t_token		*t_head_1;
	t_token_2	*t_head_2;

	t_head_1 = token_head;
	t_head_2 = token_2;
	get_input_pos(&t_head_1, &t_head_2);
	set_infile_outfile(&t_head_2);
	set_heredoc_delim(&t_head_2);
}
