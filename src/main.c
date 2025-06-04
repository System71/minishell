/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:59:43 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/04 15:03:24 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./memory/mem.h"

static t_env	*init_env(int argc, char **argv, char **envp)
{
	t_env	*cpy_env;

	(void)argc;
	(void)argv;
	cpy_env = malloc(sizeof(t_env));
	if (!cpy_env)
		return (NULL);
	cpy_env->env = env_cpy(envp);
	if (!cpy_env->env)
		exit_failure("env copy crashed");
	cpy_env->error_code = 0;
	return (cpy_env);
}

static void	destroy_file_heredoc(t_command *cmd_list)
{
	while (cmd_list)
	{
		while (cmd_list->redirs)
		{
			if (cmd_list->redirs->type == T_HEREDOC)
			{
				if (unlink(cmd_list->redirs->target) == -1)
					perror("unlink failed");
			}
			cmd_list->redirs = cmd_list->redirs->next;
		}
		cmd_list = cmd_list->next;
	}
}

char	*get_prompt(t_env *my_env)
{
	static char	prompt[64];

	snprintf(prompt, sizeof(prompt), "[%d] minishell> ", my_env->error_code);
	return (prompt);
}

void	ft_free_loop(char *input)
{
	free(input);
	mem_free_all();
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmd_list;
	t_env		*my_env;
	char		*input;

	my_env = init_env(argc, argv, envp);
	rl_event_hook = read_line_hook;
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
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (*input)
			add_history(input);
		cmd_list = parse_input(input, my_env);
		if (cmd_list != NULL)
		{
			new_pipex(cmd_list, my_env);
			destroy_file_heredoc(cmd_list);
		}
		ft_free_loop(input);
	}
	mem_free_all();
}
