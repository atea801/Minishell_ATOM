/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 16:57:37 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	res_to_tokenizer1(t_token **t_head, t_token_2 **t_head_2, char *res)
{
	if (res)
	{
		if (*t_head)
		{
			free_token_list(*t_head, *t_head_2);
			*t_head = NULL;
			*t_head_2 = NULL;
		}
		init_token_struct(t_head, t_head_2);
		// TOKENIZATION
		tokenizer(*t_head, res);
		set_token_error(t_head);
		print_token_list(*t_head);
		print_token_list_type(*t_head);
	}
}

void	my_readline(t_token **t_head, t_token_2 **t_head_2)
{
	char	*input;
	char	*res;

	while (1)
	{
		input = readline("ATOM$ ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			break ;
		}
		res = parsing_1(input);
		res_to_tokenizer1(t_head, t_head_2, res);
		if (parsing_2(*t_head, *t_head_2) > 0)
			print_redir_error(t_head);
		else if (parsing_2(*t_head, *t_head_2) == 0)
		{
			print_token_2_list_type(*t_head_2);
			check_expendable(res, *t_head_2);
		}
		add_history(input);
		if (input)
			free(input);
		if (res)
			free(res);
	}
}

int	main(int ac, char **av, char **env)
{
	t_token		*token_head;
	t_token_2	*token_2;
	t_atom_env	*env_head;

	token_head = NULL;
	token_2 = NULL;
	(void)ac;
	(void)av;
	// ENV
	if (!env || !env[0])
		create_minimal_env(&env_head);
	else
		init_all(&env_head, &token_head, env, &token_2);
	my_readline(&token_head, &token_2);
	rl_clear_history();
	if (env_head && token_head)
		// free_all(token_head, env_head, cmd_list, tab_env);
		free_all(token_head, env_head, token_2);
	return (0);
}
