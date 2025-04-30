/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:47:42 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/30 10:00:18 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../../includes/parser.h"
#include "../../includes/lib_utils.h"
#include "../memory/mem.h"

static char	*concat_segments(t_token *token)
{
	size_t			total_len;
	t_token_segment	*seg;
	char			*result;

	total_len = 0;
	seg = token->segments;
	while (seg)
	{
		total_len += ft_strlen(seg->content);
		seg = seg->next;
	}
	result = ft_xmalloc(total_len + 1);
	result[0] = '\0';
	seg = token->segments;
	while (seg)
	{
		ft_strcat(result, seg->content);
		seg = seg->next;
	}
	return (result);
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
	char			*temp_filename;
	FILE			*fp; // AUTORISER ?
	redir = ft_xmalloc(sizeof(*redir));
	if (tok->type == T_HEREDOC)
	{
		temp_filename = generate_temp_filename();
		fp = fopen(temp_filename, "w");
		if (fp == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		fputs(tok->segments->content, fp); // A VERFIER
		fclose(fp); // AUTHORISER ?
		redir->target = ft_strdup(temp_filename);
		redir->type = T_REDIRECT_IN;
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
			current_cmd = init_or_get_current_command(&cmd_list,
					current_cmd);
			if (tokens->type == T_WORD)
				process_word_token(tokens, current_cmd);
			else if (is_redirection_type(tokens->type))
				process_redirection_token(tokens, current_cmd);
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
