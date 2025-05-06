/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/06 15:46:38 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	first_children(t_command *current, int pipefd[2], int prev_fd,
		char ***my_env)
{
	// char	*error;
	// A GERER POUR LES INFILES
	// if (prev_fd == -1)
	// {
	// 	data.input_file = open(data.argv[1], O_RDONLY);
	// 	if (data.input_file == -1)
	// 	{
	// 		error("no such file or directory: ", data.argv[data.argc - 1]);
	// 		free_child_struct(data.child);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	prev_fd = data.input_file;
	// }
	// if (dup2(prev_fd, STDIN_FILENO) == -1)
	// 	error_failure("dup2 : ", "failed");
	(void)prev_fd;
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit_failure("dup2 failed\n");
	close(pipefd[0]);
	close(pipefd[1]);
	close(prev_fd);
	// if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1 || close(prev_fd) ==
	// 	-1)
	// 	exit_failure("close failed\n");
	// if (!cmd_process(current, my_env))
	// {
	// 	error = ft_strjoin(current->args[0], " commande not found\n");
	// 	exit_failure(error);
	// }
	cmd_process(current, my_env);
	exit(EXIT_FAILURE);
}

static void	last_child(t_command *current, int pipefd[2], int prev_fd,
		char ***my_env)
{
	// A GERER POUR LES OUTFILES
	// data.output_file = open(data.argv[data.argc - 1],
	// 		O_CREAT | O_RDWR | O_TRUNC, 0644);
	// if (data.output_file == -1)
	// {
	// 	error("permission denied: ", data.argv[data.argc - 1]);
	// 	free_child_struct(data.child);
	// 	exit(EXIT_FAILURE);
	// }
	if (dup2(prev_fd, STDIN_FILENO) == -1)
	{
		exit_failure("dup2 failed\n");
	}
	// if (dup2(data.output_file, STDOUT_FILENO) == -1)
	// 	error_failure("dup2 : ", "failed");
	if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1 /*
				|| close(data.output_file) == -1*/
		|| close(prev_fd) == -1)
	{
		exit_failure("close failed\n");
	}
	// if (!cmd_process(current, my_env))
	// {
	// 	exit_failure("last command not found\n");
	// 	exit(127);
	// }
	cmd_process(current, my_env);
	exit(EXIT_FAILURE);
}

static void	get_redirection(t_command *current, int *infile, int *outfile)
{
	while (current->redirs)
	{
		if (current->redirs->type == 1)
		{
			printf("il y a un infile\n");
			*infile = open(current->redirs->target, O_RDONLY);
			if (dup2(*infile, STDIN_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		else if (current->redirs->type == 2)
		{
			printf("il y a un outfile\n");
			*outfile = open(current->redirs->target, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (dup2(*outfile, STDOUT_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		else if (current->redirs->type == 3)
		{
			printf("il y a un append\n");
			*outfile = open(current->redirs->target,
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (dup2(*outfile, STDOUT_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		current->redirs = current->redirs->next;
	}
}

static void	one_command(t_command *current, char ***my_env)
{
	int	infile;
	int	outfile;

	current->pid = fork();
	if (current->pid == -1)
		exit_failure("fork : creation failed\n");
	if (current->pid == 0)
	{
		infile = 0;
		outfile = 0;
		get_redirection(current, &infile, &outfile);
		cmd_process(current, my_env);
	}
	waitpid(current->pid, current->status, 0);
}

static void	multi_command(t_command *current, char ***my_env)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = -1;
	while (current)
	{
		if (pipe(pipefd) == -1)
			exit_failure("pipe : creation failed\n");
		current->pid = fork();
		if (current->pid == -1)
			exit_failure("fork : creation failed\n");
		if (current->next && current->pid == 0)
			first_children(current, pipefd, prev_fd, my_env);
		else if (!current->next && current->pid == 0)
			last_child(current, pipefd, prev_fd, my_env);
		if (close(pipefd[1]) == -1 || (prev_fd != -1 && close(prev_fd) == -1))
			exit_failure("close failed\n");
		prev_fd = pipefd[0];
		waitpid(current->pid, current->status, 0);
		current = current->next;
	}
	if (close(pipefd[0]) == -1)
		exit_failure("close failed\n");
	// waitpid_loop(data.argc, data.child);
	// free_child_struct(data.child);
}

void	new_pipex(t_command *current, char ***my_env)
{
	// CAS AVEC UNE SEULE COMMANDE
	if (!current->next)
		one_command(current, my_env);
	// CAS AVEC PLUSIEURS COMMANDES
	else
		multi_command(current, my_env);
}
