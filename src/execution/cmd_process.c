/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 13:06:53 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *my_env)
{
	char	**paths;
	char	*substr;
	char	*extracted_path;

	while (*(my_env->env))
	{
		substr = ft_substr(*(my_env->env), 0, 5);
		if (!substr)
			return (NULL);
		if (ft_strncmp(substr, "PATH=", 5) == 0)
		{
			extracted_path = ft_substr(*(my_env->env), 5,
					ft_strlen(*(my_env->env)));
			if (!extracted_path)
			{
				exit_failure("full_path malloc extracted_path", my_env);
				free(substr);
				return (NULL);
			}
			free(substr);
			break ;
		}
		free(substr);
		(my_env->env)++;
	}
	paths = ft_split(extracted_path, ':');
	if (!paths)
	{
		free(extracted_path);
		return (NULL);
	}
	free(extracted_path);
	return (paths);
}

static void	exec_cmd(char **paths, char **args, char *end_path, t_env *my_env)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
		{
			exit_failure("full_path malloc ft_strjoin", my_env);
			return ;
		}
		execve(full_path, args, my_env->env);
		free(full_path);
	}
	if (errno == EACCES)
	{
		triple_putstr_fd("minishell: ", args[0], ": Permission denied\n", 2);
		my_env->error_code = 126;
		return ;
	}
	if (errno == ENOENT)
	{
		triple_putstr_fd("minishell: ", args[0], ": Command not found\n", 2);
		my_env->error_code = 127;
		return ;
	}
}

// if execve doesnt work we return 127
void	cmd_not_built(t_env *my_env, char **args)
{
	char	**paths;
	char	*end_path;

	execve(args[0], args, my_env->env);
	if (errno == EACCES)
	{
		triple_putstr_fd("minishell: ", args[0], ": Permission denied\n", 2);
		exit(126);
	}
	paths = get_paths(my_env);
	if (!paths)
	{
		exit_failure("get_paths", my_env);
		exit(my_env->error_code);
	}
	end_path = ft_strjoin("/", args[0]);
	if (!end_path)
	{
		exit_failure("args malloc ft_strjoin", my_env);
		free(paths);
		exit(my_env->error_code);
	}
	exec_cmd(paths, args, end_path, my_env);
	free_split(paths);
	free(end_path);
	mem_free_all(60);
	mem_free_all(8);
	exit(127);
}
// int	is_builtin(t_env *my_env, char **args)
int	is_builtin(t_env *my_env, t_command *current)
{
	if (!ft_strncmp(current->args[0], "echo", ft_strlen("echo") + 1))
		my_env->error_code = echo(current->args);
	else if (!ft_strncmp(current->args[0], "cd", ft_strlen("cd") + 1))
		my_env->error_code = cd(my_env, current->args);
	else if (!ft_strncmp(current->args[0], "pwd", ft_strlen("pwd") + 1))
		my_env->error_code = pwd(current->args, my_env);
	else if (!ft_strncmp(current->args[0], "export", ft_strlen("export") + 1))
		my_env->error_code = export(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "unset", ft_strlen("unset") + 1))
		my_env->error_code = unset(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "env", ft_strlen("env") + 1))
		my_env->error_code = env(&my_env->env);
	else if (!ft_strncmp(current->args[0], "exit", ft_strlen("exit") + 1))
		my_env->error_code = my_exit(current->args);
	else
		return (-1);
	// mem_free_all(8);
	return (0);
}
