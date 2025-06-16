/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_synthaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:17:08 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:39:40 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_syntax_err	verify_token_sequence(t_token *tokens, t_check_synt *err_data)
{
	t_token	*prev;
	t_token	*cur;

	prev = NULL;
	cur = tokens;
	while (cur)
	{
		err_data->token_err = cur;
		if (is_pipe_at_edge(prev, cur))
			return (ERR_PIPE_AT_EDGE);
		if (is_consecutive_pipes(prev, cur))
			return (ERR_CONSECUTIVE_PIPES);
		if (is_invalid_sequence(prev, cur))
			return (ERR_INVALID_SEQUENCE);
		if (is_isolated_op(prev, cur))
			return (ERR_ISOLATED_OP);
		if (is_redirect_without_word(cur))
			return (ERR_MISSING_FILENAME);
		if (is_bonus_token(cur))
			return (ERR_BONUS);
		prev = cur;
		cur = cur->next;
	}
	return (ERR_NONE);
}

bool	check_syntax(t_token *tokens, t_env *my_env)
{
	t_check_synt	err_data;

	err_data.code_err = verify_token_sequence(tokens, &err_data);
	if (err_data.code_err != ERR_NONE)
	{
		report_syntax_error(err_data.code_err,
			err_data.token_err->segments->content);
		my_env->error_code = 2;
		return (false);
	}
	return (true);
}
