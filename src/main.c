/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/18 14:30:55 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_env *my_env)
{
	static char	prompt[64];

	snprintf(prompt, sizeof(prompt), "[%d] minishell> ", my_env->error_code);
	return (prompt);
}

void	shell_loop(t_env *my_env)
{
	char		*input;
	t_command	*cmd_list;

	while (1)
	{
		set_signals_interactive();
		input = readline(get_prompt(my_env));
		if (g_signal == SIGINT)
		{
			my_env->error_code = 130;
			g_signal = 0;
			free(input);
			continue ;
		}
		if (!input)
			exit_shell();
		if (*input)
			add_history(input);
		cmd_list = parse_input(input, my_env);
		if (cmd_list)
			execute_and_cleanup(cmd_list, my_env);
		else
			my_env->error_code = 0;
		ft_free_loop(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*my_env;

	(void)argc;
	(void)argv;
	my_env = init_minishell(envp);
	shell_loop(my_env);
	mem_free_all(60);
	return (0);
}
