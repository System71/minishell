/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:48:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/20 14:52:51 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_export_or_unset(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	return (!ft_strcmp(cmd->args[0], "export")
		|| !ft_strcmp(cmd->args[0], "unset"));
}

void	process_export_unset_token(t_token *tok, t_command *current_cmd)
{
	char	*full;

	full = concat_segments(tok);
	append_arg_to_command(current_cmd, full);
}

static int	handle_expand_empty_segment(t_token_segment **seg, t_command *cmd)
{
	if ((*seg)->content && (*seg)->content[0] == '$'
		&& (*seg)->next && (*seg)->next->content
		&& (*seg)->next->content[0] == '\0')
	{
		if ((*seg)->next->next && (*seg)->next->next->content)
		{
			append_arg_to_command(cmd, ft_strdup((*seg)->next->next->content));
			*seg = (*seg)->next->next->next;
			return (1);
		}
	}
	return (0);
}

static int	handle_expand_double_quote(t_token_segment **seg, t_command *cmd)
{
	if ((*seg)->content && (*seg)->content[0] == '$'
		&& (*seg)->next && (*seg)->next->quote == QUOTE_DOUBLE)
	{
		append_arg_to_command(cmd, ft_strdup_oli((*seg)->next->content, 8));
		*seg = (*seg)->next->next;
		return (1);
	}
	return (0);
}

void	process_normal_token(t_token *tok, t_command *current_cmd)
{
	t_token_segment	*seg;

	seg = tok->segments;
	while (seg)
	{
		if (handle_expand_empty_segment(&seg, current_cmd))
			continue ;
		if (handle_expand_double_quote(&seg, current_cmd))
			continue ;
		if (seg->content)
			append_arg_to_command(current_cmd, ft_strdup_oli(seg->content, 8));
		else
			append_arg_to_command(current_cmd, ft_strdup_oli("", 8));
		seg = seg->next;
	}
}
