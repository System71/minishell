/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_synthaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 14:05:42 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include "../../includes/parsing_utils.h"
#include "../../includes/lexer.h"

bool	is_invalid_sequence(t_token *prev, t_token *cur)
{
	if (!prev)
		return (false);
	if (prev->type == T_REDIRECT_OUT && cur->type == T_REDIRECT_IN)
		return (true);
	if (prev->type == T_REDIRECT_IN && cur->type == T_REDIRECT_OUT)
		return (true);
	if (prev->type == T_APPEND && cur->type == T_AND)
		return (true);
	return (false);
}

t_syntax_err	verify_token_sequence(t_token *tokens)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = tokens;
	while (cur)
	{
		if (is_bonus_token(cur))
			return (ERR_BONUS);
		if (is_pipe_at_edge(prev, cur))
			return (ERR_PIPE_AT_EDGE);
		if (is_consecutive_pipes(prev, cur))
			return (ERR_CONSECUTIVE_PIPES);
		if (is_isolated_op(prev, cur))
			return (ERR_ISOLATED_OP);
		if (is_redirect_without_word(cur))
			return (ERR_MISSING_FILENAME);
		if (is_invalid_sequence(prev, cur))
			return (ERR_INVALID_SEQUENCE);
		prev = cur;
		cur = cur->next;
	}
	return (ERR_NONE);
}

bool	check_syntax(t_token *tokens)
{
	t_syntax_err	err;

	err = verify_token_sequence(tokens);
	if (err != ERR_NONE)
	{
		report_syntax_error(err, tokens->segments->content);
		return (false);
	}
	return (true);
}
