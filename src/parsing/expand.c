/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:54:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/22 12:01:51 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib_utils.h"
#include "../../includes/parser.h"
#include "../../includes/types.h"

// On suppose que last_exit_code 
// est une variable mise à jour après chaque commande.
int	last_exit_code = 420;

static void	expand_env(const char *in, t_expand_vars *v)
{
	size_t	s;
	size_t	l;

	s = v->i + 1;
	l = 0;
	while (ft_isalnum(in[s + l]) || in[s + l] == '_')
		l++;
	v->name = ft_strndup(in + s, l);
	// A REMPLACER GETENV
	v->value = getenv(v->name);
	if (v->value)
		append_str(&v->result, v->value);
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

char	*check_expand(const char *input, t_quote_type quote)
{
	t_expand_vars	v;

	if (quote == QUOTE_SINGLE)
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
/*char *check_expand(const char *input, t_quote_type quote)*/
/*{*/
/*    t_expand_vars  v;*/
/**/
/*    if (quote == QUOTE_SINGLE)*/
/*        return (ft_strdup(input));*/
/*    v.result = NULL;*/
/*    v.i = 0;*/
/*    while (input[v.i])*/
/*    {*/
/*        if (input[v.i] == '$' && input[v.i + 1] == '?')*/
/*        {*/
/*            v.buf = ft_itoa(last_exit_code);*/
/*            append_str(&v.result, v.buf);*/
/*            v.i += 2;*/
/*        }*/
/*        else if (input[v.i] == '$'*/
/*            && (ft_isalpha(input[v.i + 1]) || input[v.i + 1] == '_'))*/
/*        {*/
/*            v.start = v.i + 1;*/
/*            v.len = 0;*/
/*            while (input[v.start + v.len]*/
/*                && (ft_isalnum(input[v.start + v.len])*/
/*                    || input[v.start + v.len] == '_'))*/
/*                v.len++;*/
/*            v.name = ft_strndup(input + v.start, v.len);*/
/*            v.value = getenv(v.name); // NOTRE GETENV*/
/*            free(v.name);*/
/*            if (v.value)*/
/*                append_str(&v.result, v.value);*/
/*            v.i = v.start + v.len;*/
/*        }*/
/*        else*/
/*        {*/
/*            v.tmp[0] = input[v.i];*/
/*            v.tmp[1] = '\0';*/
/*            append_str(&v.result, v.tmp);*/
/*            v.i++;*/
/*        }*/
/*    }*/
/*    return (v.result);*/
/*}*/

void	expand_handle(t_token *tokens)
{
	t_token			*current;
	t_token_segment	*seg;
	char			*expanded;

	current = tokens;
	while (current)
	{
		seg = current->segments;
		while (seg)
		{
			expanded = check_expand(seg->content, seg->quote);
			free(seg->content);
			seg->content = expanded;
			seg = seg->next;
		}
		current = current->next;
	}
}
