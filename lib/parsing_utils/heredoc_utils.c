/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:13:05 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 08:18:20 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc_to_file(const char *filename, const char *content)
{
	int		fd;
	size_t	len;
	ssize_t	ret;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("minishell: open heredoc temp");
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(content);
	ret = write(fd, content, len);
	if (ret < 0 || (size_t)ret != len)
	{
		mem_free_all(8);
		perror("minishell: write heredoc temp");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	append_heredoc_line(t_heredoc *hd, const char *line)
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

void	init_hd_struct(t_heredoc *hd, t_token *curr)
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

void	destroy_file_heredoc(t_command *cmd_list)
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
