/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 14:51:51 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command *cmds;
	t_command *current;
	char *line;
	int pipefd[2];

	(void)argc;
	(void)argv;
	(void)envp;

	signals();
	current = cmds;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);

		if (pipe(pipefd) == -1)
			error_failure("pipe : ", "creation failed");
		while (cmds)
		{
			cmds->pid = fork();
			if (cmds->pid == -1)
				error_failure("fork : ", "creation failed");
			if (cmds->pid == 0)
				child(cmds, pipefd, envp);
			current = current->next;
		}

		// if (!ft_strncmp(line, "exit", 4))
		// {
		// 	free(line);
		// 	break ;
		// }
		// else if (!ft_strncmp(line, "pwd", 3))
		// 	pwd();
		// else if (!ft_strncmp(line, "echo", 5))
		// 	echo(NULL, "coucou");
		// else if (!ft_strncmp(line, "env", 3))
		// 	env(envp);
		// else if (!ft_strncmp(line, "export", 6))
		// 	export(&envp, "coucou=hello");
		// else
		// {
		// 	ft_putstr_fd(line, 2);
		// 	ft_putstr_fd(": command not found\n", 2);
		// }
		free(line);
	}
}