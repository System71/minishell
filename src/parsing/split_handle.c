/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:29 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/19 21:13:49 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*segments_to_str(t_token_segment *seg)
{
	size_t			total;
	t_token_segment	*s;
	char			*buf;

	total = 0;
	s = seg;
	while (s)
	{
		total += ft_strlen(s->content);
		s = s->next;
	}
	buf = ft_xmalloc(total + 1, 8);
	buf[0] = '\0';
	s = seg;
	while (s)
	{
		ft_strcat(buf, s->content);
		s = s->next;
	}
	return (buf);
}

static bool	need_split(t_token_segment *seg)
{
	while (seg)
	{
		if (seg->is_expand && seg->quote == QUOTE_NONE)
			return (true);
		seg = seg->next;
	}
	return (false);
}

static char	**get_split_parts(t_token *cur)
{
	char	*full;
	char	**parts;

	full = segments_to_str(cur->segments);
	if (!full)
		return (NULL);
	if (!ft_strchr(full, ' '))
	{
		return (NULL);
	}
	parts = ft_split_exec(full, ' ');
	printf("parts[0]=%s\n", parts[0]);
	return (parts);
}

static void	insert_remaining_parts(t_token *cur, char **parts, t_token *next)
{
	int		i;
	t_token	*last;
	t_token	*new;

	last = cur;
	i = 1;
	while (parts[i])
	{
		new = ft_xmalloc(sizeof(*new), 8);
		new->type = T_WORD;
		new->segments = NULL;
		add_segment_to_token(new, parts[i], QUOTE_NONE);
		last->next = new;
		last = new;
		i++;
	}
	last->next = next;
}

void	split_handle(t_token *tok_list)
{
	t_token	*cur;
	char	**parts;
	t_token	*next;

	cur = tok_list;
	while (cur)
	{
		if (cur->type == T_WORD && need_split(cur->segments))
		{
			parts = get_split_parts(cur);
			if (parts)
			{
				next = cur->next;
				rebuild_segments(cur, parts[0]);
				insert_remaining_parts(cur, parts, next);
			}
		}
		cur = cur->next;
	}
}
