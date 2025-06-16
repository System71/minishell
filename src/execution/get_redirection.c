/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:15:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 04:57:35 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_infile(t_io *io, char *file, t_env *my_env, int do_exit)
{
	if (io->infile > 2)
		close(io->infile);
	io->infile = open(file, O_RDONLY);
	if (io->infile == -1)
		exit_failure(file, my_env, do_exit);
	if (dup2(io->infile, STDIN_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

static void	handle_outfile(t_io *io, char *file, t_env *my_env, int do_exit)
{
	if (io->outfile > 2)
		close(io->outfile);
	io->outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (io->outfile == -1)
		exit_failure(file, my_env, do_exit);
	if (dup2(io->outfile, STDOUT_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

static void	handle_append(t_io *io, char *file, t_env *my_env, int do_exit)
{
	if (io->outfile > 2)
		close(io->outfile);
	io->outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (io->outfile == -1)
		exit_failure(file, my_env, do_exit);
	if (dup2(io->outfile, STDOUT_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

int	get_redirection(
	t_command *cmd, t_io *io, t_env *my_env, int do_exit)
{
	t_redirection	*redir;

	redir = cmd->redirs;
	io->infile = -1;
	io->outfile = -1;
	while (redir)
	{
		if (redir->type == T_REDIRECT_IN || redir->type == T_HEREDOC)
			handle_infile(io, redir->target, my_env, do_exit);
		else if (redir->type == T_REDIRECT_OUT)
			handle_outfile(io, redir->target, my_env, do_exit);
		else if (redir->type == T_APPEND)
			handle_append(io, redir->target, my_env, do_exit);
		redir = redir->next;
	}
	return (0);
}
