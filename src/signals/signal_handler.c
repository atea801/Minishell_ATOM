/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:55:33 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/25 10:35:54 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	handle_sigint_heredoc_parent(int sig)
{
	(void)sig;
	g_signal_received = 2;
}

void	handle_signals_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_received = 2;
	close(STDIN_FILENO);
}

void	handle_sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal_received = 1;
	// rl_redisplay();
}
