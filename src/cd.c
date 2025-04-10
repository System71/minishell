/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:27:48 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/10 15:41:14 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(char ***my_env)
{
	int	i;

	i = 0;
	while ((*my_env)[i])
	{
		if (!ft_strncmp(ft_substr((*my_env)[i], 0, 5), "HOME=", 5))
			return (ft_strchr((*my_env)[i], '=') + 1);
		i++;
	}
	return (NULL);
}

static int	go_home(char ***my_env)
{
	char	*destination;
	char	*error_destination;

	destination = get_home(my_env);
	if (!destination)
	{
		exit_failure("cd: HOME not set\n");
		return (1);
	}
	if (chdir(destination))
	{
		error_destination = ft_strjoin("minishell: cd: ", destination);
		perror(error_destination);
		return (1);
	}
	return (0);
}

static int	go_somewhere(char **full_cmd)
{
	char	*destination;
	char	*error_destination;

	destination = ft_strdup(full_cmd[1]);
	if (!destination)
	{
		exit_failure("destination malloc ft_strdup");
		return (1);
	}
	if (chdir(destination))
	{
		error_destination = ft_strjoin("minishell: cd: ", destination);
		perror(error_destination);
		return (1);
	}
	return (0);
}

int	cd(char ***my_env, char **full_cmd)
{
	if (!full_cmd[1])
		return (go_home(my_env));
	else
		return (go_somewhere(full_cmd));
	return (0);
}
