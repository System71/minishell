/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:36:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/05 13:28:50 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 == OK
// 1 == Errror
// 127 == Command not found
static int	cmd_launcher_minishell(char ***my_env, char **args)
{
	if (!ft_strncmp(args[0], "echo", ft_strlen("echo") + 1))
		return (echo(args));
	else if (!ft_strncmp(args[0], "cd", ft_strlen("cd") + 1))
		return (cd(my_env, args));
	else if (!ft_strncmp(args[0], "pwd", ft_strlen("pwd") + 1))
		return (pwd());
	else if (!ft_strncmp(args[0], "export", ft_strlen("export") + 1))
		return (export(my_env, args));
	else if (!ft_strncmp(args[0], "unset", ft_strlen("unset") + 1))
		return (unset(my_env, args));
	else if (!ft_strncmp(args[0], "env", ft_strlen("env") + 1))
		return (env(my_env));
	else if (!ft_strncmp(args[0], "exit", ft_strlen("exit") + 1))
		return (-1);
	else
		return (cmd_not_built(my_env, args));
}

int	cmd_process(t_command *current, char ***my_env)
{
	int	cmd_result;

	cmd_result = cmd_launcher_minishell(my_env, current->args);
	if (cmd_result == 1 && current->next == NULL)
	{
		return (1);
	}
	else if (cmd_result == -1 || (cmd_result == 0 && current->next == NULL))
	{
		// free(line);
		return (0);
	}
	else if (cmd_result == 127 && current->next == NULL)
	{
		// free(line);
		return (127);
	}
	else
		current = current->next;
	return (cmd_result);
}
