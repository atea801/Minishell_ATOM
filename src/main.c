/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/11/27 14:42:12 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

static int	init_shell_env(t_minishell *shell, char **env)
{
	if (!env || !env[0])
	{
		init_token_struct(&shell->tok1, &shell->tok2);
		shell->env = NULL;
		create_minimal_env(&shell->env);
		change_node_list(&shell->env, "SHLVL", "1");
	}
	else
	{
		if (getenv("_MINISHELL_RUNNING"))
		{
			ft_putstr_fd("Error: Cannot run minishell inside minishell\n", 2);
			return (1);
		}
		init_all(&shell->env, &shell->tok1, env, &shell->tok2);
		change_node_list(&shell->env, "_MINISHELL_RUNNING", "1");
	}
	return (0);
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
	if (init_shell_env(&shell, env) != 0)
		return (1);
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
