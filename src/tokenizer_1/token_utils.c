/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:34:48 by aautret           #+#    #+#             */
/*   Updated: 2025/10/17 17:42:59 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	print_token_list(t_token *head)
{
	while (head && head->value)
	{
		printf("value:%s | type:%s\n", head->value, head->type);
		head = head->next;
	}
}


void	print_token_list_type(t_token *head)
{
	printf("T_TOKEN :");
	while (head && head->value)
	{
		printf("%s ", head->type);
		head = head->next;
	}
	printf("\n");
}

/**
 * @brief copie le mot dectecter pour future tokenisation
 * (gain de lignes pour la norme)
 *
 * @param res
 * @param str
 * @param end
 * @param start
 */
void	copy_word(char *res, char *str, int end, int start)
{
	int	j;
	int	k;

	j = 0;
	k = start;
	while (k <= end)
		res[j++] = str[k++];
	res[j] = 0;
}


/**
 * @brief Set token.value et set avec appel de token_type token.type
 *
 * on passe au token suivant pour etre pret pour le prochain appel
 *
 * @param token
 * @param str
 */
int	put_token(t_token **token, char *res)
{
	(*token)->value = res;
	(*token)->type = get_token_type(res);
	(*token)->next = malloc(sizeof(t_token));
	if (!(*token)->next)
		return (1);
	(*token) = (*token)->next;
	(*token)->next = NULL;
	(*token)->value = NULL;
	(*token)->head = NULL;
	(*token)->type = NULL;
	return (0);
}

/**
 * @brief allocation de memoire pour tokenizer
 * (gain de lignes pour la norme)
 *
 * @param end
 * @param start
 * @return char*
 */
char	*malloc_token(int end, int start)
{
	char	*res;

	res = malloc(sizeof(char) * (end - start + 2));
	if (!res)
		return (NULL);
	return (res);
}