/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/03/26 15:04:34 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
void	echo(char *flag, char *str)
{
	ft_putstr_fd(str, 1);
	if (ft_strncmp(flag, "-n", 3))
		ft_putstr_fd("\n", 1);
}

void	export(char **envp, char *str)
{
	(void)envp;
	(void)str;
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
