/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/02 15:45:38 by prigaudi         ###   ########.fr       */
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
static void	exec_cmd(char **envp, char **paths, char **args, char *end_path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
			exit_failure("full_path malloc ft_strjoin");
		execve(full_path, args, envp);
		free(full_path);
	}
}
// if execve doesnt work we return 127
int	cmd_not_built(char ***my_env, char **args)
{
	char	**paths;
	char	*end_path;

	execve(args[0], args, *my_env);
	paths = get_paths(*my_env);
	if (!paths)
		return (exit_failure("get_paths"));
	end_path = ft_strjoin("/", args[0]);
	if (!end_path)
		return (exit_failure("args malloc ft_strjoin"));
	if (cmd_is_valid(paths, end_path))
		exec_cmd(*my_env, paths, args, end_path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_all(paths, args, end_path);
	exit(127);
}
int	is_builtin(t_env *my_env, char **args)
{
	if (!ft_strncmp(args[0], "echo", ft_strlen("echo") + 1))
		my_env->error_code = echo(args);
	else if (!ft_strncmp(args[0], "cd", ft_strlen("cd") + 1))
		my_env->error_code = cd(&my_env->env, args);
	else if (!ft_strncmp(args[0], "pwd", ft_strlen("pwd") + 1))
		my_env->error_code = pwd();
	else if (!ft_strncmp(args[0], "export", ft_strlen("export") + 1))
		my_env->error_code = export(&my_env->env, args);
	else if (!ft_strncmp(args[0], "unset", ft_strlen("unset") + 1))
		my_env->error_code = unset(&my_env->env, args);
	else if (!ft_strncmp(args[0], "env", ft_strlen("env") + 1))
		my_env->error_code = env(&my_env->env);
	else if (!ft_strncmp(args[0], "exit", ft_strlen("exit") + 1))
		exit(EXIT_SUCCESS);
	else
		return (-1);
	return (my_env->error_code);
}
