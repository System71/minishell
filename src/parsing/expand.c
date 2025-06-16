/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 05:00:37 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_env(const char *in, t_expand_vars *v, t_env *my_env)
{
	size_t	s;
	size_t	l;

	s = v->i + 1;
	l = 0;
	while (ft_isalnum(in[s + l]) || in[s + l] == '_')
		l++;
	v->name = ft_strndup_oli(in + s, l, 8);
	v->value = ft_getenv(v->name, my_env);
	if (v->value)
		append_str(&v->result, v->value);
	v->i = s + l;
}

static void	expand_dollar(const char *in, t_expand_vars *v, t_env *my_env)
{
	if (in[v->i + 1] == '?')
	{
		v->buf = ft_itoa(my_env->error_code);
		append_str(&v->result, v->buf);
		v->i += 2;
	}
	else if (ft_isalpha(in[v->i + 1])
		|| in[v->i + 1] == '_'
		|| in[v->i + 1] == '\0')
	{
		expand_env(in, v, my_env);
	}
	else
	{
		v->tmp[0] = '$';
		v->tmp[1] = '\0';
		append_str(&v->result, v->tmp);
		v->i++;
	}
}

static void	expand_char(const char *in, t_expand_vars *v)
{
	v->tmp[0] = in[v->i];
	v->tmp[1] = '\0';
	append_str(&v->result, v->tmp);
	v->i++;
}

char	*check_expand(const char *input, t_quote_type quote, t_token *current,
		t_env *my_env)
{
	t_expand_vars	v;

	if (quote == QUOTE_SINGLE)
		return (ft_strdup_oli(input, 8));
	if (current->type == T_HEREDOC && quote != QUOTE_NONE)
		return (ft_strdup_oli(input, 8));
	v.result = NULL;
	v.i = 0;
	while (input[v.i])
	{
		if (input[v.i] == '$')
			expand_dollar(input, &v, my_env);
		else
			expand_char(input, &v);
	}
	return (v.result);
}

void	expand_handle(t_token *tokens, t_env *my_env)
{
	t_expand_handle	handle;

	init_expand_handle(&handle, tokens);
	while (handle.current)
	{
		handle.seg = handle.current->segments;
		while (handle.seg)
		{
			handle.can_expand = (handle.seg->quote != QUOTE_SINGLE
					&& !(handle.current->type == T_HEREDOC
						&& handle.seg->quote != QUOTE_NONE));
			handle.had_dollar = (handle.can_expand
					&& ft_strchr(handle.seg->content, '$'));
			handle.old = handle.seg->content;
			if (handle.can_expand)
				handle.seg->content = check_expand(handle.old,
						handle.seg->quote, handle.current, my_env);
			else
				handle.seg->content = handle.old;
			handle.seg->is_expand = handle.had_dollar;
			handle.seg = handle.seg->next;
		}
		handle.current = handle.current->next;
	}
}
