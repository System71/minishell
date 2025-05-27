/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/27 11:35:34 by prigaudi         ###   ########.fr       */
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
	int	i;

	i = 1;
	if (!ft_strncmp(full_cmd[1], "-n", 3))
	{
		while (full_cmd[++i])
		{
			ft_putstr_fd(full_cmd[i], 1);
			if (full_cmd[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	else
	{
		while (full_cmd[i])
		{
			ft_putstr_fd(full_cmd[i], 1);
			if (full_cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}

int	env(char ***my_env)
{
	int	i;

	i = 0;
	while ((*my_env)[i])
	{
		if (ft_strrchr((*my_env)[i], '='))
		{
			ft_putstr_fd((*my_env)[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}
