/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:01 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/12 15:30:34 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <fcntl.h>
#include <unistd.h>

void	restore_std(int infile, int outfile, int saved_stdin, int saved_stdout,
		t_env *my_env, int do_exit)
{
	if (infile > 2)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, do_exit);
		close(infile);
	}
	if (outfile > 2)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			exit_failure("dup2 restore failed", my_env, do_exit);
		close(outfile);
	}
}

void	close_pipefd(int pipefd[2])
{
	if (pipefd[0] > 2)
		close(pipefd[0]);
	if (pipefd[1] > 2)
		close(pipefd[1]);
}

static void	handle_infile(
	int *infile, char *file, t_env *my_env,int do_exit)
{
	if (*infile > 2)
		close(*infile);
	*infile = open(file, O_RDONLY);
	if (*infile == -1)
		exit_failure("open failed\n", my_env, do_exit);
	if (dup2(*infile, STDIN_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

static void	handle_outfile(
	int *outfile, char *file, t_env *my_env,int do_exit)
{
	if (*outfile > 2)
		close(*outfile);
	*outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile == -1)
		exit_failure(file, my_env, do_exit);
	if (dup2(*outfile, STDOUT_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

static void	handle_append(
	int *outfile, char *file, t_env *my_env,int do_exit)
{
	if (*outfile > 2)
		close(*outfile);
	*outfile = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*outfile == -1)
		exit_failure(file, my_env, do_exit);
	if (dup2(*outfile, STDOUT_FILENO) == -1)
		exit_failure(file, my_env, do_exit);
}

int	get_redirection(
	t_command *cmd, int *infile, int *outfile, t_env *my_env,int do_exit)
{
	t_redirection	*redir;

	redir = cmd->redirs;
	*infile = -1;
	*outfile = -1;
	while (redir)
	{
		if (redir->type == T_REDIRECT_IN || redir->type == T_HEREDOC)
			handle_infile(infile, redir->target, my_env, do_exit);
		else if (redir->type == T_REDIRECT_OUT)
			handle_outfile(outfile, redir->target, my_env, do_exit);
		else if (redir->type == T_APPEND)
			handle_append(outfile, redir->target, my_env, do_exit);
		redir = redir->next;
	}
	return (0);
}
