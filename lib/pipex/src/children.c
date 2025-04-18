/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:09:05 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 08:56:46 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_children(t_data data, char *arg, int pipefd[2], int prev_fd)
{
	if (prev_fd == -1)
	{
		data.input_file = open(data.argv[1], O_RDONLY);
		if (data.input_file == -1)
		{
			error("no such file or directory: ", data.argv[data.argc - 1]);
			free_child_struct(data.child);
			exit(EXIT_FAILURE);
		}
		prev_fd = data.input_file;
	}
	if (dup2(prev_fd, STDIN_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1 || close(prev_fd)
		== -1)
		error_failure("close : ", "failed");
	if (!cmd_launcher(data.envp, arg))
	{
		error_failure(arg, ": command not found\n");
		free_child_struct(data.child);
	}
	exit(EXIT_FAILURE);
}

void	last_child(t_data data, char *arg, int pipefd[2], int prev_fd)
{
	data.output_file = open(data.argv[data.argc - 1],
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.output_file == -1)
	{
		error("permission denied: ", data.argv[data.argc - 1]);
		free_child_struct(data.child);
		exit(EXIT_FAILURE);
	}
	if (dup2(prev_fd, STDIN_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (dup2(data.output_file, STDOUT_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1
		|| close(data.output_file) == -1 || close(prev_fd) == -1)
		error_failure("close : ", "failed");
	if (!cmd_launcher(data.envp, arg))
	{
		error_failure(arg, ": command not found\n");
		free_child_struct(data.child);
		exit(127);
	}
	exit(EXIT_FAILURE);
}
