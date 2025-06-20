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

static char	*get_oldpwd(t_env *my_env)
{
	int		i;
	char	*variable_name;

	i = 0;
	while ((my_env->env)[i])
	{
		variable_name = ft_substr((my_env->env)[i], 0, 7);
		if (!variable_name)
			exit_failure("error malloc variable_name");
		if (!ft_strncmp(variable_name, "OLDPWD=", 7))
		{
			free(variable_name);
			return (ft_strchr((my_env->env)[i], '=') + 1);
		}
		i++;
		free(variable_name);
	}
	return (NULL);
}

void	update_pwd_vars(char ***envp, const char *old_pwd)
{
	char	buf[4096];
	char	oldpwd_entry[sizeof(buf)];
	char	pwd_entry[sizeof(buf)];

	if (!getcwd(buf, sizeof(buf)))
		return ;
	ft_strlcpy(oldpwd_entry, "OLDPWD=", sizeof(oldpwd_entry));
	ft_strlcat(oldpwd_entry, old_pwd, sizeof(oldpwd_entry));

	ft_strlcpy(pwd_entry, "PWD=", sizeof(pwd_entry));
	ft_strlcat(pwd_entry, buf, sizeof(pwd_entry));
	export(envp, (char *[]){"export", oldpwd_entry, pwd_entry, NULL});
}

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

int	go_home(t_env *my_env)
{
	char	old_pwd[4096];
	char	*destination;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	destination = get_home(my_env);
	if (!destination)
	{
		exit_failure("cd: HOME not set\n");
		return (1);
	}
	if (chdir(destination))
	{
		perror(destination);
		return (1);
	}
	update_pwd_vars(&my_env->env, old_pwd);
	return (0);
}


int	go_last_pwd(t_env *my_env)
{
	char	old_pwd[4096];
	char	*destination;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	destination = get_oldpwd(my_env);
	if (!destination)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (chdir(destination))
	{
		perror(destination);
		return (1);
	}
	ft_putstr_fd(destination, 1);
	ft_putstr_fd("\n", 1);
	update_pwd_vars(&my_env->env, old_pwd);
	return (0);
}

int	go_somewhere(t_env *my_env, char **args)
{
	char	old_pwd[4096];
	char	*destination;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (!ft_strcmp(args[1], "-"))
		return (go_last_pwd(my_env));
	destination = args[1];
	if (!ft_strncmp(destination, "-", 1) && ft_strlen(destination) > 1)
	{
		triple_putstr_fd("minishell: cd :",
			destination, ": invalid option\n", 2);
		return (2);
	}
	if (chdir(destination))
	{
		perror(destination);
		return (1);
	}
	update_pwd_vars(&my_env->env, old_pwd);
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
