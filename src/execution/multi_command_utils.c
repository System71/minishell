/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:12:04 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/19 18:30:27 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_loop(t_command *current, t_env *my_env)
{
	while (current)
	{
		// waitpid(current->pid, &current->status, 0);
		// void ft_last_child_status(int status)
		// {
		// 	if (WTERMSIG(status) == SIGQUIT)
		// 		ft_putstr_fd("Quit (core dumped)\n", 1);
		// 	if (WIFEXITED(status))
		// 		ft_last_return_value(WEXITSTATUS(status), 1);
		// 	else if (WIFSIGNALED(status))
		// 		ft_last_return_value(128 + WTERMSIG(status), 1);
		// }
		if (WIFEXITED(current->status))
			my_env->error_code = WEXITSTATUS(current->status);
		current = current->next;
	}
}

void	pipe_redirections(t_infileoutfile *redirections, t_command *current,
		int prev_fd, int pipefd[2])
{
	if (!redirections->infile && prev_fd)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(exit_failure("dup2 failed\n"));
	}
	if (!redirections->outfile && current->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(exit_failure("dup2 failed\n"));
	}
}

void	child(t_command *current, int pipefd[2], int prev_fd, t_env *my_env)
{
	t_infileoutfile	*redirections;

	redirections = ft_xmalloc(sizeof(t_infileoutfile), 8);
	init_redirections(redirections);
	set_signals_child();
	if (get_redirection(current, redirections, my_env))
	{
		restore_std(redirections);
		if (prev_fd)
			close(prev_fd);
		close_pipefd(pipefd);
		close_all(redirections);
		mem_free_all(8);
		mem_free_all(60);
		exit(EXIT_FAILURE);
	}
	pipe_redirections(redirections, current, prev_fd, pipefd);
	if (prev_fd)
		close(prev_fd);
	close_pipefd(pipefd);
	close_all(redirections);
	if (is_builtin(my_env, current, redirections) == -1)
		cmd_not_built(my_env, current->args);
	mem_free_all(8);
	mem_free_all(60);
	exit(EXIT_SUCCESS);
}
