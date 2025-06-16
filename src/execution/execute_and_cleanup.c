/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_cleanup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:48:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 04:24:26 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	execute_and_cleanup(t_command *cmd_list, t_env *my_env)
{
	t_io	io;

	io.infile = -1;
	io.outfile = -1;
	io.saved_stdin = dup(STDIN_FILENO);
	io.saved_stdout = dup(STDOUT_FILENO);
	if (cmd_list && !cmd_list->next && is_builtin(cmd_list))
	{
		get_redirection(cmd_list, &io, my_env, 0);
		exec_builtin(my_env, cmd_list);
		restore_std(&io, my_env, 0);
	}
	else
	{
		set_signals_wait();
		exec_pipeline(cmd_list, my_env, &io);
	}
	destroy_file_heredoc(cmd_list);
}
