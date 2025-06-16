/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:15:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 11:42:23 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_infile(t_io *io, char *file, t_env *my_env, t_exec_ctx *ctx)
{
	if (io->infile > 2)
		close(io->infile);
	io->infile = open(file, O_RDONLY);
	if (io->infile == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	if (dup2(io->infile, STDIN_FILENO) == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	return (0);
}

static int	handle_outfile(t_io *io, char *file, t_env *my_env, t_exec_ctx *ctx)
{
	if (io->outfile > 2)
		close(io->outfile);
	io->outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (io->outfile == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	if (dup2(io->outfile, STDOUT_FILENO) == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	return (0);
}

static int	handle_append(t_io *io, char *file, t_env *my_env, t_exec_ctx *ctx)
{
	if (io->outfile > 2)
		close(io->outfile);
	io->outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (io->outfile == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	if (dup2(io->outfile, STDOUT_FILENO) == -1)
	{
		exit_failure(file, my_env, io->do_exit, ctx);
		return (-1);
	}
	return (0);
}

int	get_redirection(
	t_command *cmd, t_io *io, t_env *my_env, t_exec_ctx *ctx)
{
	t_redirection	*redir;
	int				ret;

	redir = cmd->redirs;
	io->infile = -1;
	io->outfile = -1;
	while (redir)
	{
		if (redir->type == T_REDIRECT_IN || redir->type == T_HEREDOC)
			ret = handle_infile(io, redir->target, my_env, ctx);
		else if (redir->type == T_REDIRECT_OUT)
			ret = handle_outfile(io, redir->target, my_env, ctx);
		else if (redir->type == T_APPEND)
			ret = handle_append(io, redir->target, my_env, ctx);
		else
			ret = 0;
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
