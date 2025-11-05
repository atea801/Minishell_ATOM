/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/11/05 15:18:41 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	res_to_tokenizer1(t_token **t_head, t_token_2 **t_head_2, char *res)
{
	if (res)
	{
		// if (*t_head)
		// {
		// 	free_token_list(*t_head, *t_head_2);
		// 	*t_head = NULL;
		// 	*t_head_2 = NULL;
		// }
		init_token_struct(t_head, t_head_2);
		// TOKENIZER 1
		tokenizer(*t_head, res);
		set_token_error(t_head);
		// print_token_list(*t_head);
		// print_token_list_type(*t_head);
	}
}

void	my_readline(int ac, char **argv, t_minishell *shell)
{
	char		*input;
	char		*res;
	char		**env_tab;
	int			parsing_res;
	t_token		*t_head;
	t_token_2	*t_head_2;

	t_head = NULL;
	t_head_2 = NULL;
	env_tab = env_list_to_tab_new(shell->env);
	(void)ac;
	(void)argv;
	if (!env_tab)
	{
		ft_putstr_fd("Error: failed to convert env to tab\n", 2);
		return ;
	}
	// print_env_tab(env_tab);
	while (1)
	{
		if (t_head)
		{
			free_token_1_only(t_head);
			t_head = NULL;
		}
		if (t_head_2)
		{
			free_token_2_list(&t_head_2);
			t_head_2 = NULL;
		}
		shell->tok1 = NULL;
		shell->tok2 = NULL;
		shell->cmd = NULL;
		shell->should_execute = false;
		input = readline("\033[1;92mAtom > \033[0m");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			if (input)
				free(input);
			printf("exit\n");
			free_env_tab(env_tab);
			break ;
		}
		res = parsing_1(shell, input);
		if (!res)
		{
			if (input)
				free(input);
			continue ;
		}
		res_to_tokenizer1(&t_head, &t_head_2, res);
		shell->tok1 = t_head;
		shell->tok2 = t_head_2;
		parsing_res = parsing_2(shell, t_head, t_head_2);
		if (parsing_res == 0)
		{
			shell->should_execute = true;
			check_expendable(res, shell->tok2);
			expand_all_tokens(shell, shell->tok2);
			token_2_to_cmd(&shell->cmd, &shell->tok2);
			print_token_2_list(shell->tok2);
			print_cmd_list(shell->cmd);
		}
		if (shell->should_execute && shell->cmd)
		{
			env_tab = env_list_to_tab_new(shell->env);
			if (env_tab)
			{
				if (shell->cmd->next)
					execute_multipipe(shell, shell->cmd, env_tab);
				else
					exec_single_cmd(shell, shell->cmd, env_tab);
				free_env_tab(env_tab);
			}
		}
		add_history(input);
		if (input)
			free(input);
		if (res)
			free(res);
		if (shell->cmd)
		{
			free_cmd_list(shell->cmd);
			shell->cmd = NULL;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	shell;
	t_token		*t_head;
	t_token_2	*t_head_2;


	shell.tok1 = NULL;
	shell.tok2 = NULL;
	shell.cmd = NULL;
	shell.exit_code = 0;
	shell.should_execute = false;
	// if (!env || !env[0])
	// create_minimal_env(&env_head);
	// else
	init_all(&shell.env, &t_head, env, &t_head_2);
	my_readline(ac, av, &shell);
	free_all(t_head, shell.env, t_head_2);
	// rl_clear_history();
	// if (token_head || token_2)
	// 	free_token_list(token_head, token_2);
	// if (env_head)
	// 	free_env_list(env_head);
	return (0);
}
