/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:04:01 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 17:19:08 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_std(int infile, int outfile, int saved_stdin, int saved_stdout)
{
	if (infile && dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_failure("dup2 restore failed");
	if (outfile && dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_failure("dup2 restore failed");
}

void	close_pipefd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	get_redirection(t_command *current, int *infile, int *outfile)
{
	while (current->redirs)
	{
		if (current->redirs->type == T_REDIRECT_IN
			|| current->redirs->type == T_HEREDOC)
		{
			*infile = open(current->redirs->target, O_RDONLY);
			if (dup2(*infile, STDIN_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		else if (current->redirs->type == T_REDIRECT_OUT)
		{
			*outfile = open(current->redirs->target, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (dup2(*outfile, STDOUT_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		else if (current->redirs->type == T_APPEND)
		{
			*outfile = open(current->redirs->target,
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (dup2(*outfile, STDOUT_FILENO) == -1)
				exit_failure("dup2 failed");
		}
		current->redirs = current->redirs->next;
	}
}
