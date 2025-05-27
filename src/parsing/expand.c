/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/27 11:03:06 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/parsing_utils.h"
#include "../../includes/types.h"

// On suppose que last_exit_code
// est une variable mise à jour après chaque commande.
/////////////////////////
// A SUPP PAR LA SUITE

/*char *ft_getenv(const char *name)*/
/*{*/
/*    t_env *e = g_env_list;*/
/*    while (e)*/
/*    {*/
/*        if (ft_strcmp(e->key, name) == 0)*/
/*            return (e->value);*/
/*        e = e->next;*/
/*    }*/
/*    return ("");*/
/*}*/
/**/
/////////////////////////////////////////
static void	expand_env(const char *in, t_expand_vars *v)
{
	size_t	s;
	size_t	l;

	s = v->i + 1;
	l = 0;
	while (ft_isalnum(in[s + l]) || in[s + l] == '_')
		l++;
	v->name = ft_strndup(in + s, l);
	v->value = getenv(v->name); // A REMPLACER GETENV
	if (!v->value)
		append_str(&v->result, "");
	else
		append_str(&v->result, v->value);
	///// VOIR REMPLACER CE BLOC
	free(v->name);
	v->i = s + l;
}

static void	expand_dollar(const char *in, t_expand_vars *v, int error_code)
{
	if (in[v->i + 1] == '?')
	{
		v->buf = ft_itoa(error_code);
		append_str(&v->result, v->buf);
		v->i += 2;
	}
	else if (ft_isalpha(in[v->i + 1]) || in[v->i + 1] == '_')
	{
		expand_env(in, v);
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
		int error_code)
{
	t_expand_vars	v;

	if (quote == QUOTE_SINGLE)
		return (ft_strdup(input));
	if (current->type == T_HEREDOC && quote != QUOTE_NONE)
		return (ft_strdup(input));
	v.result = NULL;
	v.i = 0;
	while (input[v.i])
	{
		if (input[v.i] == '$')
			expand_dollar(input, &v, error_code);
		else
			expand_char(input, &v);
	}
	return (v.result);
}

void	init_expand_handle(t_expand_handle *handle, t_token *tokens)
{
	handle->current = tokens;
	handle->seg = NULL;
	handle->old = NULL;
	handle->can_expand = false;
	handle->had_dollar = false;
}

void	expand_handle(t_token *tokens, int error_code)
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
						handle.seg->quote, handle.current, error_code);
			else
				handle.seg->content = ft_strdup(handle.old);
			handle.seg->is_expand = handle.had_dollar;
			handle.seg = handle.seg->next;
		}
		handle.current = handle.current->next;
	}
}
