/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:19:27 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing_utils.h"
#include "../../includes/parser.h"
#include "../../includes/types.h"

// On suppose que last_exit_code 
// est une variable mise à jour après chaque commande.
int	last_exit_code = 420;
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
	v->value = getenv(v->name);// A REMPLACER GETENV
	if (!v->value)
		append_str(&v->result, "");
	else
		append_str(&v->result, v->value);
	///// VOIR REMPLACER CE BLOC
	free(v->name);
	v->i = s + l;
}

static void	expand_dollar(const char *in, t_expand_vars *v)
{
	if (in[v->i + 1] == '?')
	{
		v->buf = ft_itoa(last_exit_code);
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

char	*check_expand(const char *input, t_quote_type quote, t_token *current)
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
			expand_dollar(input, &v);
		else
			expand_char(input, &v);
	}
	return (v.result);
}

void	expand_handle(t_token *tokens)
{
	t_expand_handle	*use_handle= {0};

	use_handle->current = tokens;
	while (use_handle->current)
	{
		use_handle->seg = use_handle->current->segments;
		while (use_handle->seg)
		{
			use_handle->can_expand = (use_handle->seg->quote != QUOTE_SINGLE
				&& !(use_handle->current->type == T_HEREDOC
				&& use_handle->seg->quote != QUOTE_NONE));
			use_handle->had_dollar = (use_handle->can_expand && ft_strchr(use_handle->seg->content, '$'));
			use_handle->old = use_handle->seg->content;
			if (use_handle->can_expand)
				use_handle->seg->content = check_expand(use_handle->old, use_handle->seg->quote, use_handle->current);
			else
				use_handle->seg->content = ft_strdup(use_handle->old);
			use_handle->seg->is_expand = use_handle->had_dollar;
			(void)use_handle->old;
			use_handle->seg = use_handle->seg->next;
		}
		use_handle->current = use_handle->current->next;
	}
}
