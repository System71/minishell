/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:28:14 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 04:54:32 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_io *io, t_env *my_env, int do_exit)
{
	if (io->infile > 2)
	{
		if (dup2(io->saved_stdin, STDIN_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, do_exit);
		close(io->infile);
	}
	if (io->outfile > 2)
	{
		if (dup2(io->saved_stdout, STDOUT_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, do_exit);
		close(io->outfile);
	}
}

void	close_pipefd(int pipefd[2])
{
	if (pipefd[0] > 2)
		close(pipefd[0]);
	if (pipefd[1] > 2)
		close(pipefd[1]);
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
	if (fd > 2)
		close(fd);
}
