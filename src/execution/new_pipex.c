/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/12 15:31:07 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup2_and_close(int fd, int std)
{
	if (fd != std && fd > 2)
	{
		dup2(fd, std);
		close(fd);
	}
}

void	close_if_needed(int fd)
{
	if (fd > 2)
		close(fd);
}

static void	exec_child(
	t_command *cmd, int in_fd, int out_fd, t_env *env, int *pipefd, int has_next)
{
	int	infile;
	int	outfile;

	infile = -1;
	outfile = -1;
	get_redirection(cmd, &infile, &outfile, env);
	if (in_fd > 2)
		dup2_and_close(in_fd, 0);
	if (has_next)
	{
		if (out_fd > 2)
			dup2_and_close(out_fd, 1);
	}
	if (pipefd)
	{
		if (pipefd[0] > 2)
			close(pipefd[0]);
		if (pipefd[1] > 2)
			close(pipefd[1]);
	}
	if (infile > 2)
		dup2_and_close(infile, 0);
	if (outfile > 2)
		dup2_and_close(outfile, 1);
	if (is_builtin(env, cmd) == -1)
		execute_command(cmd->args, env->env);
	exit(0);
}

static void	pipe_and_fork(
	t_command *cmd, t_env *env, int *prev_fd, int *pipefd)
{
	pid_t	pid;
	int		out_fd;
	int		has_next;

	out_fd = 1;
	has_next = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit_failure("pipe", env);
		out_fd = pipefd[1];
		has_next = 1;
	}
	pid = fork();
	if (pid == -1)
		exit_failure("fork", env);
	if (pid == 0)
		exec_child(cmd, *prev_fd, out_fd, env, pipefd, has_next);
	cmd->pid = pid;
	close_if_needed(*prev_fd);
	if (cmd->next)
		close(pipefd[1]);
	*prev_fd = -1;
	if (cmd->next)
		*prev_fd = pipefd[0];
}

static void	wait_all(t_command *cmd)
{
	int	status;

	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
}

void	exec_pipeline(t_command *cmd, t_env *env)
{
	int		prev_fd;
	int		pipefd[2];
	t_command *curr;

	prev_fd = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
	curr = cmd;
	while (curr)
	{
		pipe_and_fork(curr, env, &prev_fd, pipefd);
		curr = curr->next;
	}
	wait_all(cmd);
}
