/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 17:20:59 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child(t_command *current, int pipefd[2], int prev_fd, t_env *my_env)
{
	int	infile;
	int	outfile;

	infile = 0;
	outfile = 0;
	get_redirection(current, &infile, &outfile);
	if (!infile && prev_fd)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit_failure("dup2 failed\n");
	}
	if (!outfile && current->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_failure("dup2 failed\n");
	}
	if (is_builtin(my_env, current) == -1)
		cmd_not_built(&my_env->env, current->args);
	close_pipefd(pipefd);
	if (prev_fd)
		close(prev_fd);
	if (infile)
		close(infile);
	if (outfile)
		close(outfile);
}

// if builtin => no fork needed
// if no builtin => fork needed
static void	one_command(t_command *current, t_env *my_env)
{
	int	infile;
	int	outfile;
	int	saved_stdout;
	int	saved_stdin;

	infile = 0;
	outfile = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	get_redirection(current, &infile, &outfile);
	if (is_builtin(my_env, current) == -1)
	{
		current->pid = fork();
		if (current->pid == -1)
			exit_failure("fork : creation failed\n");
		current->status = malloc(sizeof(int));
		if (current->pid == 0)
			cmd_not_built(&my_env->env, current->args);
		waitpid(current->pid, current->status, 0);
		if (WIFEXITED(*(current->status)))
			my_env->error_code = WEXITSTATUS(*(current->status));
	}
	restore_std(infile, outfile, saved_stdin, saved_stdout);
}

static void	multi_command(t_command *current, t_env *my_env)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = 0;
	while (current)
	{
		if (pipe(pipefd) == -1)
			exit_failure("pipe : creation failed\n");
		current->pid = fork();
		if (current->pid == -1)
			exit_failure("fork : creation failed\n");
		current->status = malloc(sizeof(int));
		if (current->pid == 0)
			child(current, pipefd, prev_fd, my_env);
		close(pipefd[1]);
		if (prev_fd)
			close(prev_fd);
		prev_fd = pipefd[0];
		waitpid(current->pid, current->status, 0);
		if (WIFEXITED(*(current->status)))
			my_env->error_code = WEXITSTATUS(*(current->status));
		current = current->next;
	}
	close(pipefd[0]);
}

void	new_pipex(t_command *current, t_env *my_env)
{
	if (!current->next)
		one_command(current, my_env);
	else
		multi_command(current, my_env);
}
