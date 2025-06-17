/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:56:33 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/02 19:38:39 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(char *line, t_heredoc hd)
{
	printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
		hd.delimiter);
	free(line);
}

void	ctrl_c(char *line, t_env *my_env)
{
	my_env->error_code = 130;
	free(line);
}

static void	handle_single_heredoc(t_token *curr, t_env *my_env)
{
	t_heredoc	hd;
	char		*line;

	rl_event_hook = read_line_hook;
	init_hd_struct(&hd, curr);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ctrl_d(line, hd);
			break ;
		}
		if (g_signal == SIGINT)
			return (ctrl_c(line, my_env));
		if (ft_strcmp(line, hd.delimiter) == 0
			|| append_heredoc_line(&hd, line) < 0)
		{
			free(line);
			break ;
		}
		hd.line_count++;
		free(line);
	}
	heredoc_storage(curr, hd);
}

void	heredoc_handle(t_token *tokens, t_env *my_env)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == T_HEREDOC)
		{
			set_signals_heredoc();
			handle_single_heredoc(curr, my_env);
			set_signals_interactive();
		}
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
}
