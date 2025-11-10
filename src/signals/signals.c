/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:55:23 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/10 10:34:38 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_received = 1;
}

void	setup_signals_prompt(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_prompt;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	restore_default_signals(void)
{
	struct sigaction	sa_sigprompt;

	sa_sigprompt.sa_handler = SIG_DFL;
	sigemptyset(&sa_sigprompt.sa_mask);
	sa_sigprompt.sa_flags = 0;
	sigaction(SIGINT, &sa_sigprompt, NULL);
	sigaction(SIGQUIT, &sa_sigprompt, NULL);
}

void	handle_signals_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal_received = sig;
	close(STDIN_FILENO);
}

void	setup_signals_heredoc(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_signals_heredoc;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
