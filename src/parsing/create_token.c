/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:22:45 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:04:00 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_segments(t_token *token)
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
	result = ft_xmalloc(total_len + 1, 8);
	result[0] = '\0';
	seg = token->segments;
	while (seg)
	{
		if (seg->content)
			ft_strcat(result, seg->content);
		seg = seg->next;
	}
	return (result);
}

t_token_segment	*create_segment(const char *content, t_quote_type quote)
{
	t_token_segment	*seg;

	seg = ft_xmalloc(sizeof(t_token_segment), 8);
	if (content == NULL)
		seg->content = ft_strdup_oli("", 8);
	else
		seg->content = ft_strdup_oli(content, 8);
	seg->quote = quote;
	seg->is_expand = false;
	seg->next = NULL;
	return (seg);
}

void	add_segment_to_token(t_token *token,
							const char *content,
							t_quote_type quote)
{
	t_token_segment	*new_seg;
	t_token_segment	*tmp;

	new_seg = create_segment(content, quote);
	if (!token->segments)
	{
		token->segments = new_seg;
	}
	else
	{
		tmp = token->segments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_seg;
	}
}

void	rebuild_segments(t_token *tok, const char *word)
{
	tok->segments = NULL;
	add_segment_to_token(tok, word, QUOTE_NONE);
}

t_token	*create_token_with_segment(const char *content, t_quote_type quote)
{
	t_token	*token;

	token = ft_xmalloc(sizeof(t_token), 8);
	if (quote == QUOTE_NONE)
		token->type = get_token_type(content);
	else
		token->type = T_WORD;
	token->segments = create_segment(content, quote);
	token->next = NULL;
	return (token);
}
