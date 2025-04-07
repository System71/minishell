/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:36:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 17:27:11 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_launcher_minishell(char ***my_env, char **full_cmd)
{
	if (!ft_strncmp(full_cmd[0], "echo", ft_strlen("echo") + 1))
		return (echo(full_cmd));
	else if (!ft_strncmp(full_cmd[0], "cd", ft_strlen("cd") + 1))
		return (cd(full_cmd));
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

int	cmd_process(t_command *cmd, char ***my_env)
{
	if (cmd->type == T_WORD)
		return (cmd_launcher_minishell(my_env, cmd->argv));
	return (1);
}