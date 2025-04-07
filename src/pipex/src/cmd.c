/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:29:09 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 10:23:44 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_all(char **paths, char **full_cmd, char *end_path)
{
	if (paths)
		free_split(paths);
	if (full_cmd)
		free_split(full_cmd);
	if (end_path)
		free(end_path);
}

// Function returns 1 if cmd in arg is valid
static int	cmd_is_valid(char **paths, char *end_path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
			error_failure("Error malloc : ", "full_path");
		if (access(full_path, X_OK) != -1)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
	}
	return (0);
}

static void	exec_cmd(char **envp, char **paths, char **full_cmd, char *end_path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
			error_failure("Error malloc : ", "full_path");
		execve(full_path, full_cmd, envp);
		free(full_path);
	}
}

int	cmd_launcher(char **envp, char *cmd)
{
	char	**paths;
	char	**full_cmd;
	char	*end_path;

	paths = get_paths(envp);
	if (!paths)
		error_failure("Error malloc : ", "paths");
	full_cmd = ft_split(cmd, ' ');
	if (!full_cmd)
		error_failure("Error malloc : ", "full_cmd");
	end_path = ft_strjoin("/", full_cmd[0]);
	if (!end_path)
		error_failure("Error malloc : ", "end_path");
	if (cmd_is_valid(paths, end_path))
		exec_cmd(envp, paths, full_cmd, end_path);
	free_all(paths, full_cmd, end_path);
	return (0);
}
