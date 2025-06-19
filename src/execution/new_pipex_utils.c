/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:01 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/19 22:04:15 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_redirections(t_infileoutfile *redir)
{
	redir->infile = 0;
	redir->outfile = 0;
	redir->saved_stdin = dup(STDIN_FILENO);
	if (redir->saved_stdin == -1)
		return (1);
	redir->saved_stdout = dup(STDOUT_FILENO);
	if (redir->saved_stdout == -1)
		return (1);
	return (0);
}

void	close_all(t_infileoutfile *redirections)
{
	if (redirections->infile)
		close(redirections->infile);
	if (redirections->outfile)
		close(redirections->outfile);
	close(redirections->saved_stdin);
	close(redirections->saved_stdout);
}

void	close_pipefd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	get_redirection(t_command *current, t_infileoutfile *redirections,
		t_env *my_env)
{
	while (current->redirs)
	{
		if (current->redirs->type == T_REDIRECT_IN
			|| current->redirs->type == T_HEREDOC)
		{
			if (redir_in(current, redirections, my_env))
				return (1);
		}
		else if (current->redirs->type == T_REDIRECT_OUT)
		{
			if (redir_out(current, &redirections->outfile, my_env))
				return (1);
		}
		else if (current->redirs->type == T_APPEND)
		{
			if (redir_out_append(current, &redirections->outfile, my_env))
				return (1);
		}
		current->redirs = current->redirs->next;
	}
	return (0);
}
