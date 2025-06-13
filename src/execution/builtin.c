/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:19:27 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/12 14:58:07 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getcwd(NULL,0) allows memory to be allocated dynamically
int	pwd(char **args, t_env *my_env)
{
	char	*buffer;
	char	*flag;

	flag = NULL;
	if (args[1] && !ft_strncmp(args[1], "-", 1))
	{
		flag = ft_substr(args[1], 0, 2);
		if (!flag)
			exit_failure("error malloc flag",my_env, 0);
		triple_putstr_fd("minishell: pwd : ", flag, ": invalid option\n", 2);
		free(flag);
		return (2);
	}
	buffer = getcwd(NULL, 0);
	if (!buffer)
		perror("pwd");
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
	free(flag);
	return (0);
}

static void	loop_flag(char **args, int *bad_flag, int *no_flag, int i)
{
	int	j;

	j = 2;
	while (args[i][j])
	{
		if (args[i][j] == 'n')
			j++;
		else
		{
			*bad_flag = 1;
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				ft_putstr_fd(" ", 1);
			break ;
		}
	}
	if (i == 1 && !(*bad_flag))
		*no_flag = 0;
}

int	echo(char **args)
{
	int	i;
	int	no_flag;
	int	bad_flag;

	no_flag = 1;
	bad_flag = 0;
	i = 1;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-n", 2) && !bad_flag)
			loop_flag(args, &bad_flag, &no_flag, i);
		else
		{
			bad_flag = 1;
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
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
