/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 17:47:04 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_command_wait(t_command *current, t_env *my_env)
{
	waitpid(current->pid, &current->status, 0);
	if (WIFEXITED(current->status))
		my_env->error_code = WEXITSTATUS(current->status);
}

// if builtin => no fork needed
// if no builtin => fork needed
static void	one_command(t_command *current, t_env *my_env)
{
	t_redirections_exec	*redirections;

	redirections = ft_xmalloc(sizeof(t_redirection), 60);
	init_redirections(redirections);
	if (!get_redirection(current, redirections, my_env))
	{
		if (is_builtin(my_env, current,redirections) == -1)
		{
			current->pid = fork();
			if (current->pid == -1)
				exit(exit_failure("fork : creation failed\n"));
			if (current->pid == 0)
			{
				close_all(redirections);
				set_signals_child();
				cmd_not_built(my_env, current->args);
			}
			one_command_wait(current, my_env);
		}
	}
	restore_std(redirections);
	close_all(redirections);
}

static void	multi_command(t_command *current, t_env *my_env)
{
	int			pipefd[2];
	int			prev_fd;
	t_command	*head;

	head = current;
	prev_fd = 0;
	while (current)
	{
		if (pipe(pipefd) == -1)
			exit(exit_failure("pipe : creation failed\n"));
		current->pid = fork();
		if (current->pid == -1)
			exit(exit_failure("fork : creation failed\n"));
		if (current->pid == 0)
			child(current, pipefd, prev_fd, my_env);
		close(pipefd[1]);
		if (prev_fd)
			close(prev_fd);
		prev_fd = pipefd[0];
		current = current->next;
	}
	current = head;
	wait_loop(current, my_env);
	close(pipefd[0]);
}

void	new_pipex(t_command *current, t_env *my_env)
{
	if (current->args == NULL || *current->args[0] == '\0')
		return ;
	if (!current->next)
		one_command(current, my_env);
	else
	{
		set_signals_wait();
		multi_command(current, my_env);
	}
}
