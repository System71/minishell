/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/20 10:37:34 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	one_command_wait(t_command *current, t_env *my_env)
{
	set_signals_wait();
	waitpid(current->pid, &current->status, 0);
	if (WTERMSIG(current->status) == SIGINT)
		ft_putchar_fd('\n', 1);
	if (WTERMSIG(current->status) == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	if (WIFEXITED(current->status))
		my_env->error_code = WEXITSTATUS(current->status);
	else if (WIFSIGNALED(current->status))
		my_env->error_code = 128 + WTERMSIG(current->status);
}

static void	one_command(t_command *current, t_env *my_env)
{
	t_infileoutfile	*redirections;

	redirections = ft_xmalloc(sizeof(t_infileoutfile), 8);
	init_redirections(redirections);
	if (!get_redirection(current, redirections, my_env))
	{
		if (current->args != NULL)
		{
			if (is_builtin(my_env, current, redirections) == -1)
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
	if (current->args == NULL)
	{
		my_env->error_code = 1;
		return ;
	}
	if (!current->next)
		one_command(current, my_env);
	else
	{
		set_signals_wait();
		multi_command(current, my_env);
	}
}
