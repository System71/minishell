/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:02:24 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/06 10:44:04 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	sigint_prompt(int signo)
{
	(void)signo;
	rl_done = 1;
	g_signal = SIGINT;
}

void	sigint_heredoc(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
	g_signal = SIGINT;
}

void	set_signals_interactive(void)
{
	signal(SIGINT, sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
