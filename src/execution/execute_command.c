/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:00:18 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 10:39:23 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **s_cmd, char **env)
{
	int		abs_path;
	char	*tmp;
	char	*path;

	abs_path = is_path_absolute_or_relative(s_cmd[0]);
	tmp = NULL;
	path = NULL;
	if (abs_path)
	{
		if (access(s_cmd[0], F_OK) == 0)
			tmp = ft_strdup(s_cmd[0]);
		return (tmp);
	}
	path = get_path(s_cmd, env);
	return (path);
}

void	check_permission(char **s_cmd, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		ft_free_tab(s_cmd);
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": permission denied\n", 2);
		free(path);
		ft_free_tab(s_cmd);
		exit(126);
	}
}

void	execute_command(char **s_cmd, char **env)
{
	char	*path;
	int		err;

	path = get_cmd_path(s_cmd, env);
	if (!path)
	{
		ft_putstr_fd(s_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(s_cmd);
		ft_free_tab(env);
		exit(127);
	}
	check_permission(s_cmd, path);
	if (execve(path, s_cmd, env) == -1)
	{
		err = errno;
		perror(s_cmd[0]);
		free(path);
		ft_free_tab(s_cmd);
		ft_free_tab(env);
		if (err == EISDIR || err == EACCES || err == ENOEXEC)
			exit(126);
		else if (err == ENOENT)
			exit(127);
		else
			exit(1);
	}
}
