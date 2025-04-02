/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/02 13:27:01 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;

	(void)argc;
	(void)argv;
	(void)envp;

	signals();

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);

		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		else if (!ft_strncmp(line, "pwd", 3))
			pwd();
		else if (!ft_strncmp(line, "echo", 5))
			echo(NULL, "coucou");
		else if (!ft_strncmp(line, "env", 3))
			env(envp);
		else if (!ft_strncmp(line, "export", 6))
			export(&envp, "coucou=hello");
		else
		{
			ft_putstr_fd(line, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		free(line);
	}
}