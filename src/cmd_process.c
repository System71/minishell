/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:36:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 17:20:39 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_launcher(char **envp, char **full_cmd)
{
	if (full_cmd[0] == "echo")
		return (echo(full_cmd));
	else if (full_cmd[0] == "cd")
		return (cd(full_cmd));
	else if (full_cmd[0] == "pwd")
		return (pwd());
	else if (full_cmd[0] == "export")
		return (export(envp, full_cmd));
	else if (full_cmd[0] == "unset")
		return (unset(envp, full_cmd));
	else if (full_cmd[0] == "env")
		return (env(envp));
	else if (full_cmd[0] == "exit")
		return (-1);
	else
		return (cmd_not_built(envp, full_cmd));
}

int	cmd_process(t_command *cmd, char **envp)
{
	if (cmd->type = T_WORD)
		return (cmd_launcher(envp, cmd->argv));
}