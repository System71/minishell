/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:06:19 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 08:56:56 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	heredoc_creation(t_data data)
{
	char	*line;

	data.input_file = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.input_file == -1)
	{
		error("permission denied: ", data.argv[data.argc - 1]);
		free_child_struct(data.child);
		exit(EXIT_FAILURE);
	}
	line = get_next_line(0);
	while (ft_strncmp(line, data.argv[2], ft_strlen(data.argv[2])
			&& ft_strlen(data.argv[2]) == ft_strlen(line))
		|| data.argv[2][0] == '\0')
	{
		write(data.input_file, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(data.input_file);
}

void	heredoc_child1(t_data data, int pipefd[2], char *arg)
{
	data.input_file = open("here_doc", O_RDONLY);
	if (data.input_file == -1)
	{
		error("permission denied: ", data.argv[data.argc - 1]);
		free_child_struct(data.child);
		exit(EXIT_FAILURE);
	}
	if (dup2(data.input_file, STDIN_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (close(pipefd[0]) == -1 || close(data.input_file) == -1)
		error_failure("close : ", "failed");
	unlink("here_doc");
	if (!cmd_launcher(data.envp, arg))
		free_child_struct(data.child);
	exit(EXIT_FAILURE);
}

void	heredoc_child2(t_data data, int pipefd[2], char *arg)
{
	data.output_file = open(data.argv[5], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data.output_file == -1)
	{
		error("permission denied: ", data.argv[data.argc - 1]);
		free_child_struct(data.child);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (dup2(data.output_file, STDOUT_FILENO) == -1)
		error_failure("dup2 : ", "failed");
	if (close(pipefd[1]) == -1)
		error_failure("close : ", "failed");
	if (!cmd_launcher(data.envp, arg))
	{
		free_child_struct(data.child);
		exit(127);
	}
	exit(EXIT_FAILURE);
}

t_child	heredoc_init_child_struct(void)
{
	t_child	child;

	child.pid = malloc(sizeof(pid_t) * 2);
	if (!child.pid)
	{
		free_child_struct(child);
		error_failure("Error malloc : ", "child");
	}
	child.status = malloc(sizeof(pid_t) * 2);
	if (!child.status)
	{
		free_child_struct(child);
		error_failure("Error malloc : ", "child");
	}
	return (child);
}
