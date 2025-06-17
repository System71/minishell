/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:01 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 18:19:48 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_redirections(t_redir_exec *redirections)
{
	redirections->infile = 0;
	redirections->outfile = 0;
	redirections->saved_stdin = dup(STDIN_FILENO);
	if (redirections->saved_stdin == -1)
		return (1);
	redirections->saved_stdout = dup(STDOUT_FILENO);
	if (redirections->saved_stdout == -1)
		return (1);
	return (0);
}

void	close_all(t_redir_exec *redirections)
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

int	get_redirection(t_command *current, t_redir_exec *redirections,
		t_env *my_env)
{
	while (current->redirs)
	{
		if (current->redirs->type == T_REDIRECT_IN
			|| current->redirs->type == T_HEREDOC)
		{
			if (redir_in(current, &redirections->infile, my_env))
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
