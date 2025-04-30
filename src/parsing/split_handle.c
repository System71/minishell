/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:44:29 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/30 14:20:51 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/types.h" 
#include "../../includes/lib_utils.h" 
#include "../memory/mem.h" 


/**
 * Crée une chaîne en concaténant tous les segments du token.
 * Utilise ft_xmalloc (mémoire libérée par mem_free_all en fin).
 */
static char	*segments_to_str(t_token_segment *seg)
{
	size_t				total;
	t_token_segment		*s;
	char				*buf;

	total = 0;
	s = seg;
	while (s)
	{
		total += ft_strlen(s->content);
		s = s->next;
	}
	buf = ft_xmalloc(total + 1);
	buf[0] = '\0';
	s = seg;
	while (s)
	{
		ft_strcat(buf, s->content);
		s = s->next;
	}
	return (buf);
}

/**
 * Reconstruit tok->segments pour n'avoir qu'un seul segment non-quoté.
 */
static void	rebuild_segments(t_token *tok, const char *word)
{
	// on écrase l'ancienne liste de segments : on oublie juste l'ancien head
	tok->segments = NULL;
	add_segment_to_token(tok, word, QUOTE_NONE);
}

/**
 * Après expand_handle, découpe chaque T_WORD dont la concaténation
 * de segments contient un IFS, et éclate en plusieurs tokens.
 */
void	split_handle(t_token *tok_list)
{
	t_token	*cur;
	t_token	*next_orig;
	char	*full;
	char	**parts;
	int		i;

	cur = tok_list;
	while (cur)
	{
		if (cur->type == T_WORD)
		{
			full = segments_to_str(cur->segments);
			if (ft_strchr(full, ' '))
			{
				parts = ft_split(full, ' ');
				rebuild_segments(cur, parts[0]);
				next_orig = cur->next;
				i = 1;
				while (parts[i])
				{
					t_token *new;

					new = ft_xmalloc(sizeof(*new));
					new->type = T_WORD;
					new->segments = NULL;
					add_segment_to_token(new, parts[i], QUOTE_NONE);
					new->next = cur->next;
					cur->next = new;
					cur = new;
					i++;
				}
				cur->next = next_orig;
			}
		}
		cur = cur->next;
	}
}

