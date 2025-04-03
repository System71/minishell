/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 14:13:12 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getcwd(NULL,0) allows memory to be allocated dynamically
void	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		perror("pwd");
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
	free(buffer);
}
void	echo(char **full_cmd)
{
	ft_putstr_fd(full_cmd[2], 1);
	if (ft_strncmp(full_cmd[1], "-n", 3))
		ft_putstr_fd("\n", 1);
}

void	env(char **envp)
{
	while (*envp)
	{
		ft_putstr_fd(*envp, 1);
		ft_putstr_fd("\n", 1);
		envp++;
	}
}

void	cd(char *full_cmd)
{
	return ;
}
void	exit_minishell(void)
{
	return ;
}
