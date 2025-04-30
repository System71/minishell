/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:56:33 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/29 20:36:54 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lib_utils.h"
#include "../../includes/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

static int	append_heredoc_line(t_heredoc *hd, const char *line)
{
	size_t	old_len;
	size_t	line_len;
	char	*new;

	old_len = hd->content_len;
	line_len = ft_strlen(line);
	new = ft_realloc(hd->content, old_len, old_len + line_len + 2);
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

static void	handle_single_heredoc(t_token *curr)
{
	t_heredoc	hd;
	char		*line;

	init_hd_struct(&hd, curr);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, hd.delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (append_heredoc_line(&hd, line) < 0)
		{
			free(line);
			break ;
		}
		hd.line_count++;
		free(line);
	}
	if (hd.content)
		curr->segments->content = hd.content;
	else
		curr->segments->content = ft_strdup("");
}

int	heredoc_handle(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == T_HEREDOC)
			handle_single_heredoc(curr);
		if (curr->next == NULL)
			break ;
		else
			curr = curr->next;
	}
	return (0);
}
