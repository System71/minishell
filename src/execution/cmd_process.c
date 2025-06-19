/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/19 19:05:17 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_paths_loop(t_env *my_env, char **extracted_path)
{
	char	*substr;
	int		i;

	i = -1;
	while ((my_env->env)[++i])
	{
		substr = ft_substr((my_env->env)[i], 0, 5);
		if (!substr)
			return (1);
		if (ft_strncmp(substr, "PATH=", 5) == 0)
		{
			*extracted_path = ft_substr((my_env->env)[i], 5,
					ft_strlen((my_env->env)[i]));
			if (!*extracted_path)
			{
				exit_failure("full_path malloc extracted_path");
				free(substr);
				return (1);
			}
			free(substr);
			break ;
		}
		free(substr);
	}
	return (0);
}

char	**get_paths(t_env *my_env)
{
	char	**paths;
	char	*extracted_path;

	extracted_path = NULL;
	if (get_paths_loop(my_env, &extracted_path))
	{
		free(extracted_path);
		return (NULL);
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
			exit_failure("full_path malloc ft_strjoin");
			return ;
		}
		execve(full_path, args, my_env->env);
		free(full_path);
	}
	if (errno == EACCES)
	{
		triple_putstr_fd("minishell: ", args[0], ": Permission denied\n", 2);
		my_env->error_code = 126;
	}
	else if (errno == ENOENT)
	{
		triple_putstr_fd("minishell: ", args[0], ": Command not found\n", 2);
		my_env->error_code = 127;
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
		mem_free_all(60);
		mem_free_all(8);
		exit(exit_failure("get_paths failed\n"));
	}
	end_path = ft_strjoin("/", args[0]);
	if (!end_path)
	{
		free(paths);
		exit(exit_failure("args malloc ft_strjoin"));
	}
	exec_cmd(paths, args, end_path, my_env);
	free_split(paths);
	free(end_path);
	mem_free_all(60);
	mem_free_all(8);
	exit(127);
}

int	is_builtin(t_env *my_env, t_command *current, t_infileoutfile *redirections)
{
	if (!ft_strncmp(current->args[0], "echo", ft_strlen("echo") + 1))
		my_env->error_code = echo(current->args);
	else if (!ft_strncmp(current->args[0], "cd", ft_strlen("cd") + 1))
		my_env->error_code = cd(my_env, current->args);
	else if (!ft_strncmp(current->args[0], "pwd", ft_strlen("pwd") + 1))
		my_env->error_code = pwd(current->args);
	else if (!ft_strncmp(current->args[0], "export", ft_strlen("export") + 1))
		my_env->error_code = export(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "unset", ft_strlen("unset") + 1))
		my_env->error_code = unset(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "env", ft_strlen("env") + 1))
		my_env->error_code = env(&my_env->env);
	else if (!ft_strncmp(current->args[0], "exit", ft_strlen("exit") + 1))
		my_env->error_code = my_exit(current->args, redirections, my_env);
	else
		return (-1);
	return (my_env->error_code);
}
