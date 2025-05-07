/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fonction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:51:03 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 10:38:25 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include "../../includes/parsing_utils.h"

bool	is_redirection_type(t_token_type type)
{
	return (type == T_REDIRECT_IN
		|| type == T_REDIRECT_OUT
		|| type == T_APPEND
		|| type == T_HEREDOC);
}

t_token_type	get_token_type(const char *str)
{
    if (ft_strcmp(str, "||") == 0)
        return (T_OR);
    else if (ft_strcmp(str, "&&") == 0)
        return (T_AND);
    else if (ft_strcmp(str, "<<") == 0)
        return (T_HEREDOC);
    else if (ft_strcmp(str, ">>") == 0)
        return (T_APPEND);
    else if (ft_strcmp(str, "|") == 0)
        return (T_PIPE);
    else if (ft_strcmp(str, "<") == 0)
        return (T_REDIRECT_IN);
    else if (ft_strcmp(str, ">") == 0)
        return (T_REDIRECT_OUT);
    else if (ft_strcmp(str, "(") == 0)
        return (T_LPAREN);
    else if (ft_strcmp(str, ")") == 0)
        return (T_RPAREN);
    else if (ft_strcmp(str, ";") == 0)
        return (T_SEMI);
    else if (ft_strcmp(str, "&") == 0)
        return (T_BG);
    return (T_WORD);
}

bool	is_special_char(char c)
{
    return c == '>' || c == '<'
        || c == '|' || c == '&'
        || c == ';' || c == '('
        || c == ')';
}
