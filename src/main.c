/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/11/24 12:43:09 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static char	*get_dynamic_prompt_protect(void)
{
	char	*directory;
	char	*prompt_start;
	char	*prompt_mid;
	char	*prompt;

	directory = "Minishell";
	prompt_start = ft_strjoin("\033[1;92m", directory);
	prompt_mid = ft_strjoin(prompt_start, " > ");
	prompt = ft_strjoin(prompt_mid, "\033[0m");
	free(prompt_start);
	free(prompt_mid);
	return (prompt);
}

char	*get_dynamic_prompt(void)
{
	char	*cwd;
	char	*directory;
	char	*prompt_start;
	char	*prompt_mid;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (get_dynamic_prompt_protect());
	directory = ft_strrchr(cwd, '/');
	if (directory && directory[1])
		directory++;
	else if (directory && ft_strcmp(cwd, "/") == 0)
		directory = "/";
	else
		directory = "Minishell";
	prompt_start = ft_strjoin("\033[1;92m", directory);
	prompt_mid = ft_strjoin(prompt_start, " > ");
	prompt = ft_strjoin(prompt_mid, "\033[0m");
	free(cwd);
	free(prompt_start);
	free(prompt_mid);
	return (prompt);
}

void	res_to_tokenizer1(t_minishell *shell)
{
	if (shell->buffers.res)
	{
		if (shell->tok1)
		{
			free_token_1_only(shell->tok1);
			shell->tok1 = NULL;
		}
		if (shell->tok2)
		{
			free_token_2_list(&shell->tok2);
			shell->tok2 = NULL;
		}
		init_token_struct(&shell->tok1, &shell->tok2);
		tokenizer(shell->tok1, shell->buffers.res);
		set_token_error(&shell->tok1);
	}
}

void	my_readline(int ac, char **argv, t_minishell *shell)
{
	int		parsing_res;
	size_t	len;

	// char		**env_tab;
	// t_cmd		*current;
	len = 0;
	len = 0;
	(void)ac;
	(void)argv;
	// je suis inquiet de ce com je pense que ca servait possiblement
	// a quelque chose...
	// env_tab = env_list_to_tab_new(shell->env);
	// if (!env_tab)
	// {
	// 	ft_putstr_fd("Minishell: Error: failed to convert env to tab\n", 2);
	// 	return ;
	// }
	while (1)
	{
		if (shell->tok1)
		{
			free_token_1_only(shell->tok1);
			(shell->tok1) = NULL;
		}
		if (shell->tok2)
		{
			free_token_2_list(&shell->tok2);
			shell->tok2 = NULL;
		}
		if (shell->cmd)
		{
			free_cmd_list(shell->cmd);
			shell->cmd = NULL;
		}
		shell->tok1 = NULL;
		shell->tok2 = NULL;
		shell->should_execute = false;
		shell->buffers.prompt = NULL;
		shell->buffers.input = NULL;
		shell->buffers.prompt = get_dynamic_prompt();
		if (isatty(STDIN_FILENO))
			shell->buffers.input = readline(shell->buffers.prompt);
		if (!shell->buffers.input || ft_strcmp(shell->buffers.input,
				"exit") == 0)
		{
			if (shell->buffers.input)
				free(shell->buffers.input);
			if (shell->buffers.prompt)
				free(shell->buffers.prompt);
			printf("exit\n");
			if (shell->cmd)
			{
				free_cmd_list(shell->cmd);
				shell->cmd = NULL;
			}
			break ;
		}
		shell->buffers.res = parsing_1(shell, shell->buffers.input);
		if (!shell->buffers.res)
		{
			if (shell->buffers.input)
				free(shell->buffers.input);
			if (shell->buffers.prompt)
				free(shell->buffers.prompt);
			continue ;
		}
		if (!shell->buffers.res)
		{
			if (shell->buffers.input)
				free(shell->buffers.input);
			if (shell->buffers.prompt)
				free(shell->buffers.prompt);
			continue ;
		}
		if (g_signal_received == 1)
			shell->exit_code = 130;
		res_to_tokenizer1(shell);
		// print_token_list(shell->tok1);
		parsing_res = parsing_2(shell, shell->tok1, shell->tok2);
		if (parsing_res == 0)
		{
			shell->should_execute = true;
			check_expendable(shell->buffers.res, shell->tok2);
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
					exec_single_cmd(shell);
			}
			else
			{
				close_all_cmd_fds(shell->cmd);
			}
		}
		/* Restore prompt signals after command execution completes */
		if (isatty(STDIN_FILENO))
			setup_signals_prompt();
		if (shell->should_exit)
		{
			if (shell->buffers.input)
				free(shell->buffers.input);
			if (shell->buffers.res)
				free(shell->buffers.res);
			if (shell->cmd)
			{
				free_cmd_list(shell->cmd);
				shell->cmd = NULL;
			}
			if (shell->buffers.prompt)
				free(shell->buffers.prompt);
			break ;
		}
		if (isatty(STDIN_FILENO) && shell->buffers.input
			&& *shell->buffers.input)
			add_history(shell->buffers.input);
		if (shell->buffers.input)
			free(shell->buffers.input);
		if (shell->buffers.res)
			free(shell->buffers.res);
		if (shell->buffers.prompt)
			free(shell->buffers.prompt);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	shell;

	shell.tok1 = NULL;
	shell.tok2 = NULL;
	shell.cmd = NULL;
	shell.exit_code = 0;
	shell.should_execute = false;
	shell.should_exit = false;
	if (!env || !env[0])
	{
		init_token_struct(&shell.tok1, &shell.tok2);
		shell.env = NULL;
		create_minimal_env(&shell.env);
	}
	else
		init_all(&shell.env, &shell.tok1, env, &shell.tok2);
	setup_signals_prompt();
	my_readline(ac, av, &shell);
	if (shell.tok1)
		free_token_1_only(shell.tok1);
	if (shell.tok2)
		free_token_2_list(&shell.tok2);
	if (shell.cmd)
		free_cmd_list(shell.cmd);
	if (shell.env)
		free_env_list(shell.env);
	rl_clear_history();
	return (shell.exit_code);
}
