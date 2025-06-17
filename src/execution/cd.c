/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:27:48 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 15:00:07 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// faire fonction pour MAJ pwd et old pwd dans env
static char	*get_home(t_env *my_env)
{
	int		i;
	char	*variable_name;

	i = 0;
	while ((*(my_env->env))[i])
	{
		variable_name = ft_substr((my_env->env)[i], 0, 5);
		if (!variable_name)
		{
			exit_failure("error malloc variable_name");
			return (NULL);
		}
		if (!ft_strncmp(variable_name, "HOME=", 5))
		{
			free(variable_name);
			return (ft_strchr((my_env->env)[i], '=') + 1);
		}
		i++;
		free(variable_name);
	}
	return (NULL);
}

static int	go_home(t_env *my_env)
{
	char	*destination;

	destination = get_home(my_env);
	if (!destination)
		return (exit_failure("cd: HOME not set\n"));
	if (chdir(destination))
	{
		perror(destination);
		return (1);
	}
	return (0);
}

static int	go_last_pwd(t_env *my_env)
{
	int		i;
	char	*destination;
	char	*variable_name;

	i = 0;
	while ((my_env->env)[i])
	{
		variable_name = ft_substr((my_env->env)[i], 0, 7);
		if (!variable_name)
			return (exit_failure("error malloc variable_name"));
		if (!ft_strncmp(variable_name, "OLDPWD=", 7))
		{
			destination = ft_strchr((my_env->env)[i], '=') + 1;
			free(variable_name);
			break ;
		}
		i++;
		free(variable_name);
	}
	if (chdir(destination))
		return (exit_failure("No such file or directory\n"));
	ft_putstr_fd(destination, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

static int	go_somewhere(t_env *my_env, char **args)
{
	char	*destination;

	destination = ft_strdup_oli(args[1], 8);
	if (!destination)
	{
		exit_failure("destination malloc ft_strdup\n");
		return (1);
	}
	if (!ft_strcmp(args[1], "-"))
		return (go_last_pwd(my_env));
	if (!ft_strncmp(&(args[1][0]), "-", 1) && ft_strlen(args[1]) > 1)
	{
		triple_putstr_fd("minishell: cd :", ft_substr(args[1], 0, 2),
			": invalid option\n", 2);
		return (2);
	}
	if (chdir(destination))
	{
		perror(destination);
		return (1);
	}
	return (0);
}

int	cd(t_env *my_env, char **args)
{
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (go_home(my_env));
	else if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else
		return (go_somewhere(my_env, args));
}
