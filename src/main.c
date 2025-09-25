/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/09/25 16:54:36 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	main(void)
{
	char	*input;
	char	*res;
	t_token	*token;
	t_token	*head;

	head = malloc(sizeof(t_token));
	token = head;
	while (1)
	{
		input = readline("ATOM$ ");
		if (!input || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			printf("exit\n");
			break ;
		}
		res = parsing_1(input);
		if (res)
		{
			//TOKENIZATION
			tokenizer(token, res);
			print_token_list(head);
			print_token_list_type(head);
			add_history(input);
		}
		// printf("Vous avez tapé : %s\n", input);
		free(res);
		free(input);
	}
	rl_clear_history();
	return (0);
}

