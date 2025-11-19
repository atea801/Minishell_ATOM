/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/11/19 16:09:41 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Get the dynamic prompt object
 * 
 * @return char* 
 * @note prompt = ft_strjoin(directory, " > ");

 */
char	*get_dynamic_prompt(void)
{
	char	*cwd;
	char	*directory;
	char	*prompt_start;
	char	*prompt_mid;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	directory = ft_strrchr(cwd, '/');
	if (directory && directory[1])
		directory++;
	else if (directory && ft_strcmp(cwd, "/") == 0)
		directory = "/";
	else
		directory = "Atom";
	prompt_start = ft_strjoin("\033[1;92m", directory);
	prompt_mid = ft_strjoin(prompt_start, " > ");
	prompt = ft_strjoin(prompt_mid, "\033[0m");
	free(cwd);
	free(prompt_start);
	free(prompt_mid);
	return (prompt);
}

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
	char		*prompt;
	int			parsing_res;
	t_token		*t_head;
	t_token_2	*t_head_2;
	size_t		len;
	// ssize_t		nread;

	// t_cmd		*current;
	t_head = NULL;
	t_head_2 = NULL;
	len = 0;
	(void)ac;
	(void)argv;
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
		if (shell->cmd)
		{
			free_cmd_list(shell->cmd);
			shell->cmd = NULL;
		}
		shell->tok1 = NULL;
		shell->tok2 = NULL;
		shell->should_execute = false;
		prompt = NULL;
		input = NULL;
		prompt = get_dynamic_prompt();
		if (isatty(STDIN_FILENO))
			input = readline(prompt);
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			if (input)
				free(input);
			free(prompt);
			printf("exit\n");
			if (shell->cmd)
			{
				free_cmd_list(shell->cmd);
				shell->cmd = NULL;
			}
			break ;
		}
		res = parsing_1(shell, input);
		if (!res)
		{
			if (input)
				free(input);
			free(prompt);
			continue ;
		}
		if (!res)
		{
			if (input)
				free(input);
			free(prompt);
			continue ;
		}
		res_to_tokenizer1(&t_head, &t_head_2, res);
		shell->tok1 = t_head;
		shell->tok2 = t_head_2;
		// print_token_list(shell->tok1);
		parsing_res = parsing_2(shell, t_head, t_head_2);
		if (parsing_res == 0)
		{
			shell->should_execute = true;
			check_expendable(res, shell->tok2);
			expand_all_tokens(shell, shell->tok2);
			token_2_to_cmd(&shell->cmd, &shell->tok2);
			// print_token_2_list(shell->tok2);
			// print_cmd_list(shell->cmd);
		}
		if (shell->should_execute && shell->cmd)
		{
			count_and_extract_heredocs(shell->cmd);
			if (process_heredocs(shell->cmd, shell) == 0)
			{
				if (shell->cmd->next)
					execute_multipipe(shell, shell->cmd);
				else
					exec_single_cmd(shell, shell->cmd);
			}
		}
		if (isatty(STDIN_FILENO))
			setup_signals_prompt();
		if (shell->should_exit)
		{
			if (input)
				free(input);
			if (res)
				free(res);
			if (shell->cmd)
			{
				free_cmd_list(shell->cmd);
				shell->cmd = NULL;
			}
			if (prompt)
				free(prompt);
			break ;
		}
		if (isatty(STDIN_FILENO) && input && *input)
			add_history(input);
		if (input)
			free(input);
		if (res)
			free(res);
		if (prompt)
			free(prompt);
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
	shell.should_exit = false;
	// if (!env || !env[0])
	// create_minimal_env(&env_head);
	// else
	init_all(&shell.env, &t_head, env, &t_head_2);
	setup_signals_prompt();
	my_readline(ac, av, &shell);
	// free_all(t_head, shell.env, t_head_2);
	if (t_head)
		free_token_1_only(t_head);
	if (t_head_2)
		free_token_2_list(&t_head_2);
	if (shell.cmd)
		free_cmd_list(shell.cmd);
	if (shell.env)
		free_env_list(shell.env);
	rl_clear_history();
	return (shell.exit_code);
}
