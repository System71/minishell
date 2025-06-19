/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/16 14:04:36 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *current)
{
	if (!current->args || !current->args[0])
		return (0);
	if (!ft_strncmp(current->args[0], "echo", 5))
		return (1);
	if (!ft_strncmp(current->args[0], "cd", 3))
		return (1);
	if (!ft_strncmp(current->args[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(current->args[0], "export", 7))
		return (1);
	if (!ft_strncmp(current->args[0], "unset", 6))
		return (1);
	if (!ft_strncmp(current->args[0], "env", 4))
		return (1);
	if (!ft_strncmp(current->args[0], "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(t_env *my_env, t_command *current, bool child)
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
		my_env->error_code = my_exit(current->args, my_env);
	if (child)
	{
		mem_free_all(8);
		mem_free_all(60);
	}
	return (0);
}
