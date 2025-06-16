/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:36:31 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 07:07:16 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_fds(t_exec_ctx *ctx)
{
	if (ctx->in_fd > 2)
		dup2_and_close(ctx->in_fd, STDIN_FILENO);
	if (ctx->has_next && ctx->out_fd > 2)
		dup2_and_close(ctx->out_fd, STDOUT_FILENO);
}

static void	close_child_pipes(int *pipefd)
{
	if (!pipefd)
		return ;
	if (pipefd[0] > 2)
		close(pipefd[0]);
	if (pipefd[1] > 2)
		close(pipefd[1]);
}

static void	dup_redir_fds(t_io *io)
{
	if (io->infile > 2)
		dup2_and_close(io->infile, STDIN_FILENO);
	if (io->outfile > 2)
		dup2_and_close(io->outfile, STDOUT_FILENO);
}

static void	run_child_command(t_exec_ctx *ctx)
{
	char	**args;
	char	**my_env;

	if (is_builtin(ctx->cmd))
		exec_builtin(ctx->env, ctx->cmd);
	else
	{
		args = ft_strdup_tab(ctx->cmd->args);
		my_env = ft_strdup_tab(ctx->env->env);
		execute_command(args, my_env);
	}
}

void	exec_child(t_exec_ctx *ctx)
{
	get_redirection(ctx->cmd, ctx->io, ctx->env, 1);
	setup_child_fds(ctx);
	close_child_pipes(ctx->pipefd);
	dup_redir_fds(ctx->io);
	run_child_command(ctx);
	exit(0);
}
