/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:56:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 14:50:32 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(char **paths, char **full_cmd, char *end_path)
{
	if (paths)
		free_split(paths);
	if (full_cmd)
		free_split(full_cmd);
	if (end_path)
		free(end_path);
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
			error_failure("Error malloc : ", "full_path");
		if (access(full_path, X_OK) != -1)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
	}
	return (0);
}

static void	exec_cmd(char **envp, char **paths, char **full_cmd, char *end_path)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], end_path);
		if (!full_path)
			error_failure("Error malloc : ", "full_path");
		execve(full_path, full_cmd, envp);
		free(full_path);
	}
}

void	cmd_not_built(char **envp, char **full_cmd)
{
	char	**paths;
	char	**full_cmd;
	char	*end_path;

	paths = get_paths(envp);
	if (!paths)
		error_failure("Error malloc : ", "paths");
	full_cmd = ft_split(full_cmd[0], ' ');
	if (!full_cmd)
		error_failure("Error malloc : ", "full_cmd");
	end_path = ft_strjoin("/", full_cmd[0]);
	if (!end_path)
		error_failure("Error malloc : ", "end_path");
	if (cmd_is_valid(paths, end_path))
		exec_cmd(envp, paths, full_cmd, end_path);
	free_all(paths, full_cmd, end_path);
}

int	cmd_launcher(char **envp, char **full_cmd)
{
	if (full_cmd[0] == "echo")
		echo(full_cmd);
	else if (full_cmd[0] == "cd")
		cd(full_cmd);
	else if (full_cmd[0] == "pwd")
		pwd();
	else if (full_cmd[0] == "export")
		export(envp, full_cmd);
	else if (full_cmd[0] == "unset")
		unset(envp, full_cmd);
	else if (full_cmd[0] == "env")
		env(envp);
	else if (full_cmd[0] == "exit")
		exit_minishell();
	else
	{
		cmd_not_built(envp, full_cmd);
	}
	return (0);
}

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
// A VOIR SI ON LAISSE DANS LE MAIN OU PAS !!!!
// int	pipe_cmd(t_command cmds, char **envp, int nbr_cmd)
// {
// 	int pipefd[2];
// 	pid_t *pid;

// 	if (pipe(pipefd) == -1)
// 		error_failure("pipe : ", "creation failed");
// 	while (nbr_cmd > 0)
// 	{
// 		if (pid == -1)
// 			error_failure("fork : ", "creation failed");
// 		if (pid == 0)
// 			child(cmds, pipefd, envp);
// 	}
// }
