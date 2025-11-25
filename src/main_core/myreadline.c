/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myreadline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:36:01 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 18:54:45 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	my_readline(int ac, char **argv, t_minishell *shell)
{
	(void)ac;
	(void)argv;
	while (1)
	{
		free_all_buffers(shell);
		prepare_prompt_and_input(shell);
		if (handle_exit(shell))
			break ;
		if (handle_parsing_and_errors(shell))
			continue ;
		execute_commands_if_ready(shell);
		if (handle_exit(shell))
			break ;
		add_input_to_history(shell);
	}
}
