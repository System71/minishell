/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/20 11:11:16 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(t_env *my_env, char *input,
						t_command *cmd_list, size_t i)
{
	while (1)
	{
		set_signals_interactive();
		input = readline("minishell> ");
		if (g_signal == SIGINT)
		{
			my_env->error_code = 130;
			g_signal = 0;
			free(input);
			continue ;
		}
		if (!input)
			exit_shell(my_env);
		if (*input)
			add_history(input);
		i = 0;
		cmd_list = parse_input(input + i, my_env);
		if (cmd_list)
			execute_and_cleanup(cmd_list, my_env);
		ft_free_loop(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*my_env;
	char		*input;
	t_command	*cmd_list;
	size_t		i;

	i = 0;
	input = NULL;
	cmd_list = NULL;
	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
		return (1);
	(void)argc;
	(void)argv;
	my_env = init_minishell(envp);
	shell_loop(my_env, input, cmd_list, i);
	mem_free_all(60);
	return (0);
}
