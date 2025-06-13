/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:48:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:26:12 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	execute_and_cleanup(t_command *cmd_list, t_env *my_env)
{
	int	saved_stdin;
	int	saved_stdout;

	if (cmd_list && !cmd_list->next && is_builtin(cmd_list))
	{
		saved_stdin = dup(0);
		saved_stdout = dup(1);
		int infile = -1;
		int outfile = -1;
		get_redirection(cmd_list, &infile, &outfile, my_env, 0);
		exec_builtin(my_env, cmd_list);
		restore_std(infile, outfile, saved_stdin, saved_stdout, my_env, 0);
	}
	else
	{
		exec_pipeline(cmd_list, my_env);
	}

	destroy_file_heredoc(cmd_list);
}