/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:16:30 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/18 14:36:07 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std(t_redir_exec *redirections)
{
	if (redirections->infile && (dup2(redirections->saved_stdin,
				STDIN_FILENO) == -1))
		exit_failure("dup2 restoire failed\n");
	if (redirections->outfile && dup2(redirections->saved_stdout,
			STDOUT_FILENO) == -1)
		exit_failure("dup2 restore failed\n");
}

static int	my_dup2(t_command *current, int file, t_env *my_env, int old_std)
{
	if (dup2(file, old_std) == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror(current->redirs->target);
		my_env->error_code = 1;
		return (1);
	}
	return (0);
}

int	redir_in(t_command *current, int *infile, t_env *my_env)
{
	*infile = open(current->redirs->target, O_RDONLY);
	if (*infile == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror(current->redirs->target);
		my_env->error_code = 1;
		return (1);
	}
	if (my_dup2(current, *infile, my_env, STDIN_FILENO))
		return (1);
	return (0);
}

int	redir_out(t_command *current, int *outfile, t_env *my_env)
{
	*outfile = open(current->redirs->target, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror(current->redirs->target);
		my_env->error_code = 1;
		return (1);
	}
	if (my_dup2(current, *outfile, my_env, STDOUT_FILENO))
		return (1);
	return (0);
}

int	redir_out_append(t_command *current, int *outfile, t_env *my_env)
{
	*outfile = open(current->redirs->target, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*outfile == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror(current->redirs->target);
		my_env->error_code = 1;
		return (1);
	}
	if (my_dup2(current, *outfile, my_env, STDOUT_FILENO))
		return (1);
	return (0);
}
