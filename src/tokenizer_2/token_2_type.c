/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:06:04 by tlorette          #+#    #+#             */
/*   Updated: 2025/10/07 16:46:16 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Alloue l'espace necessaire pour la structure token_2->next
 *
 * @param token_2
 */
void	put_token_2(t_token_2 **token_2)
{
	t_token_2	*token_head_2;

	token_head_2 = *token_2;
	if (!token_head_2->next)
	{
		token_head_2->next = malloc(sizeof(t_token_2));
		if (!token_head_2->next)
			return ;
		token_head_2->next->value = NULL;
		token_head_2->next->type = NULL;
		token_head_2->next->next = NULL;
	}
}

/**
 * @brief Alloue la taille de l'input CMD
 *
 * @param str
 * @return char*
 */
char	*malloc_cmd(char *str)
{
	int		count;
	char	*cmd;

	count = ft_strlen(str);
	cmd = malloc(sizeof(char) * count + 1);
	if (!cmd)
		return (NULL);
	return (cmd);
}

/**
 * @brief Copie et alloue le contenu de token (token->value)
 *
 * @param str
 * @return char*
 */
char	*copy_token_value(char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = malloc_cmd(str);
	while (str[i])
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = 0;
	return (cmd);
}

t_token_2	*get_input_pos(t_token **token_1, t_token_2 **token_2)
{
	t_token_2	*token_head_2;
	t_token		*token_head_1;
	int			first_word;

	token_head_1 = *token_1;
	token_head_2 = *token_2;
	first_word = 0;
	if (!token_head_1)
		return (NULL);
	while (token_head_1 && token_head_1->type)
	{
		first_word = get_pos(token_head_1, token_head_2, first_word);
		token_head_2 = token_head_2->next;
		token_head_1 = token_head_1->next;
	}
	return (token_head_2);
}

int	get_pos(t_token *token_head_1, t_token_2 *token_head_2, int first_word)
{
	put_token_2(&token_head_2);
	if (first_word == 0 && ft_strcmp(token_head_1->type, "MOT") == 0)
	{
		fill_cmd(&token_head_1, &token_head_2);
		first_word = 1;
	}
	else if (first_word == 1 && ft_strcmp(token_head_1->type, "MOT") == 0)
		fill_args(&token_head_1, &token_head_2);
	else
	{
		fill_heredoc_append(&token_head_1, &token_head_2);
		fill_redirin_redirout(&token_head_1, &token_head_2);
		first_word = 0;
	}
	return (first_word);
}
