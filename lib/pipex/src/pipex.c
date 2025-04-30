/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:35:07 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/30 16:00:02 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	waitpid_loop(int argc, t_child child)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < argc - 3)
	{
		waitpid(child.pid[i], &child.status[i], 0);
		if (i == argc - 4 && WIFEXITED(child.status[i]))
		{
			exit_code = WEXITSTATUS(child.status[i]);
			if (exit_code == 1 || exit_code == 127)
			{
				free_child_struct(child);
				exit(exit_code);
			}
		}
		i++;
	}
}

static t_child	init_child_struct(t_data data)
{
	t_child	child;

	child.pid = malloc(sizeof(pid_t) * (data.argc - 3));
	if (!child.pid)
	{
		free_child_struct(child);
		error_failure("Error malloc : ", "child");
	}
	child.status = malloc(sizeof(pid_t) * (data.argc - 3));
	if (!child.status)
	{
		free_child_struct(child);
		error_failure("Error malloc : ", "child");
	}
	return (child);
}

static void	pipex(t_data data)
{
	int	pipefd[2];
	int	prev_fd;
	int	i;

	prev_fd = -1;
	i = -1;
	while (++i < data.argc - 3)
	{
		if (pipe(pipefd) == -1)
			error_failure("pipe : ", "creation failed");
		data.child.pid[i] = fork();
		if (data.child.pid[i] == -1)
			error_failure("fork : ", "creation failed");
		if (i == data.argc - 4 && data.child.pid[i] == 0)
			last_child(data, data.argv[i + 2], pipefd, prev_fd);
		else if (data.child.pid[i] == 0)
			first_children(data, data.argv[i + 2], pipefd, prev_fd);
		if (close(pipefd[1]) == -1 || (prev_fd != -1 && close(prev_fd) == -1))
			error_failure("close : ", "failed");
		prev_fd = pipefd[0];
	}
	if (close(pipefd[0]) == -1)
		error_failure("close : ", "failed");
	waitpid_loop(data.argc, data.child);
	free_child_struct(data.child);
}

static void	pipex_heredoc(t_data data)
{
	int	pipefd[2];

	heredoc_creation(data);
	if (pipe(pipefd) == -1)
		error_failure("pipe : ", "creation failed");
	data.child.pid[0] = fork();
	if (data.child.pid[0] == -1)
		error_failure("fork : ", "creation failed");
	if (data.child.pid[0] == 0)
		heredoc_child1(data, pipefd, data.argv[3]);
	data.child.pid[1] = fork();
	if (data.child.pid[1] == -1)
		error_failure("fork : ", "creation failed");
	if (data.child.pid[1] == 0)
		heredoc_child2(data, pipefd, data.argv[4]);
	if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1)
		error_failure("close : ", "failed");
	free_child_struct(data.child);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5)
	{
		error("arg", ": argument number is not valid");
		exit(0);
	}
	if (!envp)
	{
		error("envp", ": doesn't exist");
		exit(0);
	}
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	if (!ft_strncmp(data.argv[1], "here_doc", 8))
	{
		data.child = heredoc_init_child_struct();
		pipex_heredoc(data);
	}
	else
	{
		data.child = init_child_struct(data);
		pipex(data);
	}
}
