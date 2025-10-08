/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/10/08 18:26:07 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

int	main(int ac, char **av, char **env)
{
	char		*input;
	char		*res;
	t_token		*token_head;
	t_token_2	*token_2;
	t_atom_env	*env_head;
	t_cmd		*cmd_list;

	// char		**tab_env;
	token_head = NULL;
	token_2 = NULL;
	env_head = NULL;
	cmd_list = NULL;
	(void)ac;
	(void)av;
	// ENV
	if (!env || !env[0])
	{
		create_minimal_env(&env_head);
		print_env_list(env_head);
	}
	else
		init_all(&env_head, &token_head, &cmd_list, env, &token_2);
	// tab_env = env_list_to_tab(env_head);
	// print_env_tab(tab_env);
	while (1)
	{
		input = readline("ATOM$ ");
		if (!input || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			printf("exit\n");
			break ;
		}
		// PARSING 1
		res = parsing_1(input);
		if (res)
		{
			if (token_head && token_2)
			{
				free_token_list(token_head, token_2);
				token_head = NULL;
			}
			init_token_struct(&token_head, &token_2);
			// TOKENIZATION
			tokenizer(token_head, res);
			print_token_list(token_head);
			print_token_list_type(token_head);
			// PARSING 2
			if (parsing_2(token_head, token_2) > 0)
			{
				printf("Parse 2 as break\n");
				break ;
			}
			print_token_2_list_type(token_2);
			check_expendable(res, token_2);
			add_history(input);
		}
		// printf("Vous avez tapé : %s\n", input);
		free(res);
		free(input);
	}
	rl_clear_history();
	if (env_head && token_head && cmd_list)
		// free_all(token_head, env_head, cmd_list, tab_env);
		free_all(token_head, env_head, cmd_list, token_2);
	return (0);
}
