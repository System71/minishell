/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 17:24:01 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	char	**paths;
	char	*substr;
	char	*extracted_path;

	while (*envp)
	{
		substr = ft_substr(*envp, 0, 5);
		if (!substr)
			return (NULL);
		if (ft_strncmp(substr, "PATH=", 5) == 0)
		{
			extracted_path = ft_substr(*envp, 5, ft_strlen(*envp));
			free(substr);
			break ;
		}
		free(substr);
		envp++;
	}
	paths = ft_split(extracted_path, ':');
	if (!paths)
		return (NULL);
	free(extracted_path);
	return (paths);
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
			exit_failure("full_path malloc ft_strjoin");
		if (access(full_path, X_OK) != -1)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
	}
	return (0);
}
// ATTENTION ON A BESOIN DE CREER UN PROCESSUS ENFANT POUR NE PAS QUITTER LE PROGRAMME APRES EXECUTION DE EXECVE !!!!
static void	exec_cmd(char **envp, char **paths, char **full_cmd, char *end_path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
			exit_failure("full_path malloc ft_strjoin");
		execve(full_path, full_cmd, envp);
		free(full_path);
	}
}
int	cmd_not_built(char ***my_env, char **full_cmd)
{
	char	**paths;
	char	*end_path;

	paths = get_paths(*my_env);
	if (!paths)
		return (exit_failure("get_paths"));
	full_cmd = ft_split(full_cmd[0], ' ');
	if (!full_cmd)
		return (exit_failure("full_cmd malloc ft_split"));
	end_path = ft_strjoin("/", full_cmd[0]);
	if (!end_path)
		return (exit_failure("full_cmd malloc ft_strjoin"));
	if (cmd_is_valid(paths, end_path))
		exec_cmd(*my_env, paths, full_cmd, end_path);
	free_all(paths, full_cmd, end_path);
	return (127);
}
