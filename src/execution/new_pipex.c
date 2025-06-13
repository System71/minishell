/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:40:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/12 15:31:07 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab_dup(char **tab)
{
	int i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_strdup_tab(char **tab)
{
	int		count;
	char	**dup;
	int		i;

	if (!tab)
		return (NULL);
	count = 0;
	while (tab[count])
		count++;
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
		{
			// Libère tout si erreur d'allocation partielle
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[count] = NULL;
	return (dup);
}

void	dup2_and_close(int fd, int std)
{
	if (fd != std && fd > 2)
	{
		dup2(fd, std);
		close(fd);
	}
}

void	close_if_needed(int fd)
{
	if (fd > 2)
		close(fd);
}

static void	exec_child(
	t_command *cmd, int in_fd, int out_fd, t_env *env, int *pipefd, int has_next)
{
	int	infile;
	int	outfile;

	infile = -1;
	outfile = -1;
	get_redirection(cmd, &infile, &outfile, env, 1);
	if (in_fd > 2)
		dup2_and_close(in_fd, 0);
	if (has_next)
	{
		if (out_fd > 2)
			dup2_and_close(out_fd, 1);
	}
	if (pipefd)
	{
		if (pipefd[0] > 2)
			close(pipefd[0]);
		if (pipefd[1] > 2)
			close(pipefd[1]);
	}
	if (infile > 2)
		dup2_and_close(infile, 0);
	if (outfile > 2)
		dup2_and_close(outfile, 1);
	if (is_builtin(cmd))
	{
		exec_builtin(env, cmd);
		mem_free_all(8);
		mem_free_all(60);
	}
	else
	{
		char **args = ft_strdup_tab(cmd->args);
		char **my_env = ft_strdup_tab(env->env);
		mem_free_all(8);
		mem_free_all(60);
		execute_command(args, my_env);
	}
	exit(0);
}

static void	pipe_and_fork(
	t_command *cmd, t_env *env, int *prev_fd, int *pipefd)
{
	pid_t	pid;
	int		out_fd;
	int		has_next;

	out_fd = 1;
	has_next = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			exit_failure("pipe", env, 0);
		out_fd = pipefd[1];
		has_next = 1;
	}
	pid = fork();
	if (pid == -1)
		exit_failure("fork", env, 0);
	if (pid == 0)
		exec_child(cmd, *prev_fd, out_fd, env, pipefd, has_next);
	cmd->pid = pid;
	close_if_needed(*prev_fd);
	if (cmd->next)
		close(pipefd[1]);
	*prev_fd = -1;
	if (cmd->next)
		*prev_fd = pipefd[0];
}

static void	wait_all(t_command *cmd, t_env *env)
{
	int	status;
	int	last_status;

	last_status = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		last_status = status;
		cmd = cmd->next;
	}
	if (WIFEXITED(last_status))
		env->error_code = WEXITSTATUS(last_status);
	else
		env->error_code = 1;
}

void	exec_pipeline(t_command *cmd, t_env *env)
{
	int		prev_fd;
	int		pipefd[2];
	t_command *curr;

	prev_fd = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
	curr = cmd;
	while (curr)
	{
		pipe_and_fork(curr, env, &prev_fd, pipefd);
		curr = curr->next;
	}
	wait_all(cmd, env);
}
