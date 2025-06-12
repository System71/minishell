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

static int	append_heredoc_line(t_heredoc *hd, const char *line)
{
	size_t	old_len;
	size_t	line_len;
	char	*new;

	old_len = hd->content_len;
	line_len = ft_strlen(line);
	new = ft_realloc(hd->content, old_len, old_len + line_len + 2, 8);
	if (!new)
	{
		free(hd->content);
		return (-1);
	}
	ft_memcpy(new + old_len, line, line_len);
	new[old_len + line_len] = '\n';
	new[old_len + line_len + 1] = '\0';
	hd->content = new;
	hd->content_len = old_len + line_len + 1;
	return (0);
}

static void	init_hd_struct(t_heredoc *hd, t_token *curr)
{
	hd->delimiter = curr->segments->content;
	hd->content = NULL;
	hd->content_len = 0;
	hd->line_count = 0;
}

void	heredoc_storage(t_token *curr, t_heredoc hd)
{
	if (hd.content)
		curr->segments->content = hd.content;
	else
		curr->segments->content = ft_strdup_oli("", 8);
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
		if (g_signal == SIGINT)
		{
			//bash: warning: here-document at line 19 delimited by end-of-file (wanted `L')
			printf("LOLOL\n");
			my_env->error_code = 130;
			free(line);
			return ;
		}
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
