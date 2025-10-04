/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/10/04 14:24:14 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	char		*res;
	t_token		*token_head;
	t_atom_env	*env_head;

	token_head = NULL;
	env_head = NULL;
	(void)ac;
	(void)av;
	// ENV
	if (!env || !env[0])
	{
		create_minimal_env(&env_head);
		print_env_list(env_head);
	}
	else
		init_all(&env_head, &token_head, env);
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
			// TOKENIZATION
			tokenizer(token_head, res);
			print_token_list(token_head);
			print_token_list_type(token_head);
			add_history(input);
		}
		// printf("Vous avez tapé : %s\n", input);
		free(res);
		free(input);
	}
	rl_clear_history();
	if (env_head || token_head)
		free_all(token_head, env_head);
	return (0);
}
