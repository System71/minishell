/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/05/28 21:16:33 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./memory/mem.h"

static t_env	*init_env(int argc, char **argv, char **envp)
{
	t_env		*cpy_env;

	(void)argc;
	(void)argv;
	signals();
	cpy_env = malloc(sizeof(t_env));
	cpy_env->env = env_cpy(envp);
	if (!cpy_env->env)
		exit_failure("env copy crashed");
	cpy_env->error_code = 0;
	return(cpy_env);
}

static void destroy_file_heredoc(t_command *cmd_list)
{
	while (cmd_list)
	{
		while(cmd_list->redirs)
		{
			if (cmd_list->redirs->type == T_HEREDOC)
			{
				if (unlink(cmd_list->redirs->target) == -1	)
    				perror("unlink failed");	
			}
			cmd_list->redirs = cmd_list->redirs->next;
		}
	  	cmd_list = cmd_list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_env		*my_env;
	char		*input;


	my_env = init_env(argc, argv, envp);
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
		cmd_list = parse_input(input, my_env);
		print_commands(cmd_list);
		if (cmd_list != NULL)
		{
			new_pipex(cmd_list, my_env);
			destroy_file_heredoc(cmd_list);
		}
		free(input);
	}
	mem_free_all();
}
