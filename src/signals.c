/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:02:24 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/28 21:16:31 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Action to Ctrl-C
static void	sigint_act(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(void)
{
	struct sigaction sa;

	sa.sa_handler = &sigint_act;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL))
		perror("sigaction");
}
