/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/27 14:04:33 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./memory/mem.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_command	*current;
	t_env		*my_env;
	char		*input;

	(void)argc;
	(void)argv;
	signals();
	my_env = malloc(sizeof(t_env));
	my_env->env = env_cpy(envp);
	if (!my_env->env)
		exit_failure("env copy crashed");
	my_env->error_code = 0;
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
		cmd_list = parse_input(input, my_env->error_code);
		print_commands(cmd_list);
		// Pourquoi redefinir cmd_list a current ?
		// Il faudra une protection
		// if (cmd_list != NULL)
		// new_pipex(...);
		current = cmd_list;
		new_pipex(current, my_env);
		free(input);
		// AJOUTER SUPPRESSION FICHIER TEMPORAIRE HEREDOC
	}
	mem_free_all();
}
