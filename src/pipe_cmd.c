/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:56:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 10:46:13 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_command *cmds, int pipefd[2], char **envp)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1)
		error_failure("close : ", "failed");
	if (!cmd_launcher(envp, cmds->argv))
	{
		error_failure(cmds->argv[0], ": command not found\n");
	}
	exit(EXIT_FAILURE);
}
