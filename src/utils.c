/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:15 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/20 10:13:02 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eacces_exit(char *arg, int err)
{
	if (err == EACCES)
		triple_putstr_fd("minishell: ", arg, ": Permission denied!!!!\n", 2);
	else if (err == EISDIR)
		triple_putstr_fd("minishell: ", arg, ": Is a directory\n", 2);
	else if (err == ENOEXEC)
		triple_putstr_fd("minishell: ", arg, ": Exec format error\n", 2);
	mem_free_alls();
	exit(126);
}

void	triple_putstr_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}

void	exit_shell(t_env *my_env)
{
	int	error_code;

	error_code = my_env->error_code;
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	mem_free_all(60);
	exit(error_code);
}

// PASSAGE EN VOID A VOIR
int	exit_failure(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
