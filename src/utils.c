/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:15 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/12 14:52:03 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	triple_putstr_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}

void	exit_shell(void)
{
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	mem_free_all(60);
	exit(0);
}

// PASSAGE EN VOID A VOIR
void	exit_failure(char *message, t_env *my_env, int do_exit)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	my_env->error_code = 1;
	if (do_exit)
	{
		mem_free_all(8);
		exit(1);
	}
}
