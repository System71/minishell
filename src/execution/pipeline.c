/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:48:56 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 12:51:37 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_pipe_and_ctx(
	t_pipe_ctx *pctx, t_command *cmd)
{
	pctx->pipefd[0] = -1;
	pctx->pipefd[1] = -1;
	if (cmd->next)
	{
		if (pipe(pctx->pipefd) == -1)
			exit_failure("pipe", pctx->env, 0, NULL);
	}
}

static void	fork_and_exec(
	t_command *cmd, t_pipe_ctx *pctx)
{
	pid_t		pid;
	t_exec_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(t_exec_ctx));
	ctx.cmd = cmd;
	ctx.env = pctx->env;
	ctx.io = pctx->io;
	ctx.in_fd = pctx->prev_fd;
	ctx.out_fd = pctx->pipefd[1];
	ctx.pipefd = pctx->pipefd;
	ctx.has_next = (cmd->next != NULL);
	ctx.io->do_exit = 1;
	pid = fork();
	if (pid == -1)
		exit_failure("fork", pctx->env, 0, NULL);
	if (pid == 0)
	{
		set_signals_child();
		exec_child(&ctx);
	}
	cmd->pid = pid;
}

static void	wait_all(t_command *cmd, t_env *env)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		last_status = status;
		cmd = cmd->next;
	}
	if (WIFEXITED(last_status))
	{
		env->error_code = WEXITSTATUS(last_status);
	}
	else if (WIFSIGNALED(last_status))
	{
		printf("terminated by signal %d\n", WTERMSIG(last_status));
		env->error_code = 128 + WTERMSIG(last_status);
	}
	else
		env->error_code = 1;
}

void	exec_pipeline(t_command *cmd, t_env *env, t_io *io)
{
	t_pipe_ctx	pctx;
	t_command	*curr;

	pctx.prev_fd = -1;
	pctx.io = io;
	pctx.env = env;
	curr = cmd;
	while (curr)
	{
		setup_pipe_and_ctx(&pctx, curr);
		fork_and_exec(curr, &pctx);
		close_if_needed(pctx.prev_fd);
		if (curr->next)
			close(pctx.pipefd[1]);
		pctx.prev_fd = -1;
		if (curr->next)
			pctx.prev_fd = pctx.pipefd[0];
		curr = curr->next;
	}
	cleanup_pipe_ctx(&pctx);
	wait_all(cmd, env);
}
