/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/04 14:53:39 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getcwd(NULL,0) allows memory to be allocated dynamically
int	pwd(char **args)
{
	char	*buffer;

	if (args[1] && !ft_strncmp(args[1], "-", 1))
	{
		ft_putstr_fd("minishell: pwd : ", 2);
		ft_putstr_fd(ft_substr(args[1], 0, 2), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
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
	int	j;
	int	no_flag;
	int	bad_flag;

	no_flag = 1;
	bad_flag = 0;
	i = 1;
	while (full_cmd[i])
	{
		if (!ft_strncmp(full_cmd[i], "-n", 2) && !bad_flag)
		{
			j = 2;
			while (full_cmd[i][j])
			{
				if (full_cmd[i][j] == 'n')
					j++;
				else
				{
					bad_flag = 1;
					ft_putstr_fd(full_cmd[i], 1);
					if (full_cmd[i + 1])
						ft_putstr_fd(" ", 1);
					break ;
				}
			}
			if (i == 1 && !bad_flag)
				no_flag = 0;
		}
		else
		{
			bad_flag = 1;
			ft_putstr_fd(full_cmd[i], 1);
			if (full_cmd[i + 1])
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (no_flag && bad_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	env(char ***my_env)
{
	int i;

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