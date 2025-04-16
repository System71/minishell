/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:36:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/16 14:59:38 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 == OK
// 1 == Errror
// 127 == Command not found
static int	cmd_launcher_minishell(char ***my_env, char **full_cmd)
{
	if (!ft_strncmp(full_cmd[0], "echo", ft_strlen("echo") + 1))
		return (echo(full_cmd));
	else if (!ft_strncmp(full_cmd[0], "cd", ft_strlen("cd") + 1))
		return (cd(my_env, full_cmd));
	else if (!ft_strncmp(full_cmd[0], "pwd", ft_strlen("pwd") + 1))
		return (pwd());
	else if (!ft_strncmp(full_cmd[0], "export", ft_strlen("export") + 1))
		return (export(my_env, full_cmd));
	else if (!ft_strncmp(full_cmd[0], "unset", ft_strlen("unset") + 1))
		return (unset(my_env, full_cmd));
	else if (!ft_strncmp(full_cmd[0], "env", ft_strlen("env") + 1))
		return (env(my_env));
	else if (!ft_strncmp(full_cmd[0], "exit", ft_strlen("exit") + 1))
		return (-1);
	else
		return (cmd_not_built(my_env, full_cmd));
}

int	cmd_process(t_command *current, char ***my_env)
{
	int	cmd_result;
	int	i;

	i = 0;
	while (current->args[i])
	{
		printf("args[%d]=%s\n", i, current->args[i]);
		i++;
	}
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
