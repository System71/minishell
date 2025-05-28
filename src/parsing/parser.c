/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/28 16:16:19 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../../includes/parser.h"
#include "../../includes/parsing_utils.h"
#include "../memory/mem.h"
#include <unistd.h>
#include <fcntl.h>

static void	write_heredoc_to_file(const char *filename, const char *content)
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
		mem_free_all();
		perror("minishell: write heredoc temp");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	process_word_token(t_token *tok, t_command *current_cmd)
{
	char	*arg;

	arg = concat_segments(tok);
	append_arg_to_command(current_cmd, arg);
}

static t_redirection	*build_redirection(t_token *tok)
{
	t_redirection	*redir;
	char			*tmp;

	redir = ft_xmalloc(sizeof * redir);
	if (tok->type == T_HEREDOC)
	{
		tmp = generate_temp_filename();
		if (!tmp)
			exit(EXIT_FAILURE);
		write_heredoc_to_file(tmp, tok->segments->content);
		redir->target = tmp;
		/*redir->type = T_REDIRECT_IN;*/
	}
	else
	{
		redir->target = concat_segments(tok);
		redir->type = tok->type;
	}
	redir->next = NULL;
	return (redir);
}

static void	process_redirection_token(t_token *tok, t_command *current_cmd)
{
	t_redirection	*redir;
	t_redirection	*last;

	redir = build_redirection(tok);
	if (current_cmd->redirs == NULL)
	{
		current_cmd->redirs = redir;
	}
	else
	{
		last = current_cmd->redirs;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = redir;
	}
}

t_command	*parse_commands(t_token *tokens)
{
	t_command	*cmd_list;
	t_command	*current_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (tokens != NULL)
	{
		if (tokens->type == T_PIPE)
		{
			current_cmd = NULL;
		}
		else
		{
			current_cmd = init_or_get_current_command(&cmd_list, current_cmd);
			if (tokens->type == T_WORD)
				process_word_token(tokens, current_cmd);
			else if (is_redirection_type(tokens->type))
				process_redirection_token(tokens, current_cmd);
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
