/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/22 15:39:06 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./memory/mem.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_command	*current;
	char		**my_env;
	char		*input;

	(void)argc;
	(void)argv;
	signals();
	my_env = env_cpy(envp);
	if (!my_env)
		exit_failure("env copy crashed");
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*input)
			add_history(input);
		cmd_list = parse_input(input);
		print_commands(cmd_list);
		// Pourquoi redefinir cmd_list a current ?
		// Il faudra une protection
		// if (cmd_list != NULL)
		// new_pipex(...);
		current = cmd_list;
		new_pipex(current, &my_env);
		free(input);
	}
	mem_free_all();
}
