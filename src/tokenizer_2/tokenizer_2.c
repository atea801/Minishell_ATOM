/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:54:05 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 13:24:31 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

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
	while (t_head_2->next && t_head_2->next->type)
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
}
