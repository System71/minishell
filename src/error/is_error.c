/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:08:16 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 14:08:45 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"

bool	is_bonus_token(t_token *cur)
{
	return (cur->type == T_OR
		|| cur->type == T_AND
		|| cur->type == T_LPAREN
		|| cur->type == T_RPAREN);
}

bool	is_pipe_at_edge(t_token *prev, t_token *cur)
{
	return (cur->type == T_PIPE
		&& (prev == NULL || cur->next == NULL));
}

bool	is_consecutive_pipes(t_token *prev, t_token *cur)
{
	return (cur->type == T_PIPE
		&& prev != NULL
		&& prev->type == T_PIPE);
}

bool	is_isolated_op(t_token *prev, t_token *cur)
{
	return ((cur->type == T_SEMI || cur->type == T_BG)
		&& (prev == NULL || cur->next == NULL));
}

bool	is_redirect_without_word(t_token *cur)
{
	if (cur->type == T_REDIRECT_IN
		|| cur->type == T_HEREDOC
		|| cur->type == T_REDIRECT_OUT
		|| cur->type == T_APPEND)
	{
		return (cur->next == NULL
			|| cur->next->type != T_WORD);
	}
	return (false);
}
