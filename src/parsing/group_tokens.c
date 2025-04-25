/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:25:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/16 09:03:58 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"
#include <unistd.h>
#include <stdio.h>

static t_token_segment	*duplicate_segments(t_token_segment *seg)
{
	t_token_segment	*new_seg;

	if (!seg)
		return (NULL);
	new_seg = create_segment(seg->content, seg->quote);
	if (!new_seg)
		return (NULL);
	new_seg->next = duplicate_segments(seg->next);
	return (new_seg);
}

static void	free_token_segments(t_token *token)
{
	t_token_segment	*seg;
	t_token_segment	*tmp;

	seg = token->segments;
	while (seg)
	{
		tmp = seg;
		seg = seg->next;
		free(tmp->content);
		free(tmp);
	}
	token->segments = NULL;
}

t_token	*group_tokens(t_token *tokens)
{
	t_token	*curr;
	t_token	*to_remove;

	curr = tokens;
	while (curr)
	{
		if (is_redirection_type(curr->type))
		{
			if (curr->next && curr->next->type == T_WORD)
			{
				free_token_segments(curr);
				curr->segments = duplicate_segments(curr->next->segments);
				to_remove = curr->next;
				curr->next = to_remove->next;
				free(to_remove);
			}
			else
			{
				write(2, "Error syntax: redirection without target.\n", 42);
			}
		}
		curr = curr->next;
	}
	return (tokens);
}
