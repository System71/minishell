/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/02 14:45:19 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_redirection(t_command *current, int *infile, int *outfile)
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

static void	child(t_command *current, int pipefd[2], int prev_fd, t_env *my_env)
{
	int	infile;
	int	outfile;

	infile = 0;
	outfile = 0;
	get_redirection(current, &infile, &outfile);
	if (!infile && prev_fd)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit_failure("dup2 failed\n");
	}
	if (!outfile && current->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_failure("dup2 failed\n");
	}
	cmd_not_built(&my_env->env, current->args);
	close(pipefd[0]);
	close(pipefd[1]);
	if (prev_fd)
		close(prev_fd);
	if (infile)
		close(infile);
	if (outfile)
		close(outfile);
}

// if builtin => no fork needed
// if no builtin => fork needed
static void	one_command(t_command *current, t_env *my_env)
{
	int	infile;
	int	outfile;

	if (is_builtin(my_env, current->args) == -1)
	{
		current->pid = fork();
		if (current->pid == -1)
			exit_failure("fork : creation failed\n");
		current->status = malloc(sizeof(int));
		if (current->pid == 0)
		{
			infile = 0;
			outfile = 0;
			get_redirection(current, &infile, &outfile);
			cmd_not_built(&my_env->env, current->args);
		}
		waitpid(current->pid, current->status, 0);
		if (WIFEXITED(*(current->status)))
			my_env->error_code = WEXITSTATUS(*(current->status));
	}
}

static void	multi_command(t_command *current, t_env *my_env)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = 0;
	while (current)
	{
		if (pipe(pipefd) == -1)
			exit_failure("pipe : creation failed\n");
		current->pid = fork();
		if (current->pid == -1)
			exit_failure("fork : creation failed\n");
		current->status = malloc(sizeof(int));
		if (current->pid == 0)
			child(current, pipefd, prev_fd, my_env);
		close(pipefd[1]);
		if (prev_fd)
			close(prev_fd);
		prev_fd = pipefd[0];
		waitpid(current->pid, current->status, 0);
		if (WIFEXITED(*(current->status)))
			my_env->error_code = WEXITSTATUS(*(current->status));
		current = current->next;
	}
	close(pipefd[0]);
}

void	new_pipex(t_command *current, t_env *my_env)
{
	// CAS AVEC UNE SEULE COMMANDE
	if (!current->next)
	{
		one_command(current, my_env);
	}
	// CAS AVEC PLUSIEURS COMMANDES
	else
		multi_command(current, my_env);
}
