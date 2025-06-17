/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:28:14 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 13:06:51 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_io *io, t_env *my_env)
{
	if (io->infile > 2)
	{
		if (dup2(io->saved_stdin, STDIN_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, io->do_exit, NULL);
		close(io->infile);
	}
	if (io->outfile > 2)
	{
		if (dup2(io->saved_stdout, STDOUT_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, io->do_exit, NULL);
		close(io->outfile);
	}
}

void	cleanup_pipe_ctx(t_pipe_ctx *pctx)
{
	close_if_needed(pctx->prev_fd);
	close_pipefd(pctx->pipefd);
}

void	close_pipefd(int pipefd[2])
{
	if (!pipefd)
		return ;
	close_if_needed(pipefd[0]);
	close_if_needed(pipefd[1]);
}

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
	if (fd != -1 && fd > 2 && fd < 1024)
		close(fd);
}
