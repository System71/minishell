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

void	restore_std(int infile, int outfile, int saved_stdin, int saved_stdout,
		t_env *my_env)
{
	if (infile && dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_failure("dup2 restore failed", my_env);
	if (outfile && dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_failure("dup2 restore failed", my_env);
}

void	close_pipefd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	get_redirection(t_command *current, int *infile, int *outfile,
		t_env *my_env)
{
	while (current->redirs)
	{
		if (current->redirs->type == T_REDIRECT_IN
			|| current->redirs->type == T_HEREDOC)
		{
			*infile = open(current->redirs->target, O_RDONLY);
			if (*infile == -1)
			{
				exit_failure("open failed\n", my_env);
				return (1);
			}
			if (dup2(*infile, STDIN_FILENO) == -1)
			{
				exit_failure("dup2 failed\n", my_env);
				return (1);
			}
		}
		else if (current->redirs->type == T_REDIRECT_OUT)
		{
			*outfile = open(current->redirs->target, O_CREAT | O_RDWR | O_TRUNC,
					0644);
			if (*outfile == -1)
			{
				exit_failure("open failed\n", my_env);
				return (1);
			}
			if (dup2(*outfile, STDOUT_FILENO) == -1)
			{
				exit_failure("dup2 failed\n", my_env);
				return (1);
			}
		}
		else if (current->redirs->type == T_APPEND)
		{
			*outfile = open(current->redirs->target,
					O_CREAT | O_RDWR | O_APPEND, 0644);
			if (*outfile == -1)
			{
				exit_failure("open failed\n", my_env);
				return (1);
			}
			if (dup2(*outfile, STDOUT_FILENO) == -1)
			{
				exit_failure("dup2 failed\n", my_env);
				return (1);
			}
		}
		current->redirs = current->redirs->next;
	}
	return (0);
}
