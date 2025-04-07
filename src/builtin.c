/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 18:07:33 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getcwd(NULL,0) allows memory to be allocated dynamically
int	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		perror("pwd");
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
	free(buffer);
	return (0);
}
int	echo(char **full_cmd)
{
	ft_putstr_fd(full_cmd[2], 1);
	if (ft_strncmp(full_cmd[1], "-n", 3))
		ft_putstr_fd("\n", 1);
	return (0);
}

int	env(char ***my_env)
{
	while (**my_env)
	{
		ft_putstr_fd(**my_env, 1);
		ft_putstr_fd("\n", 1);
		(*my_env)++;
	}
	return (0);
}

int	cd(char **full_cmd)
{
	(void)full_cmd;
	return (0);
}
int	exit_minishell(void)
{
	return (0);
}
