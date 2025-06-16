/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 07:02:46 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 07:09:04 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_path_absolute_or_relative(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '/')
		return (1);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	if (cmd[0] == '.')
	{
		if (cmd[1] == '.' && cmd[2] == '/')
			return (1);
	}
	return (0);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*find_executable(char **allpath, char **cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = 0;
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (!path_part)
			ft_free_double_tab(allpath, cmd);
		exec = ft_strjoin(path_part, cmd[0]);
		free(path_part);
		if (!exec)
			ft_free_double_tab(allpath, cmd);
		if (access(exec, F_OK) == 0)
		{
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(allpath);
	return (NULL);
}

char	*get_path(char **cmd, char **env)
{
	char	*env_path;
	char	**allpath;
	char	*exec;

	env_path = my_getenv("PATH", env);
	if (!env_path)
		return (NULL);
	allpath = ft_split(env_path, ':');
	if (!allpath)
		exit(-1);
	exec = find_executable(allpath, cmd);
	return (exec);
}
