/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/20 15:14:09 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(const char *input, t_env *my_env)
{
	t_token		*tokens;
	t_command	*cmd_list;

	tokens = lexer(input);
	if (!check_syntax(tokens, my_env))
	{
		mem_free_all(8);
		return (NULL);
	}
	tokens = group_tokens(tokens);
	heredoc_handle(tokens, my_env);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		mem_free_all(8);
		return (NULL);
	}
	expand_handle(tokens, my_env);
	split_handle(tokens);
	cmd_list = parse_commands(tokens);
	return (cmd_list);
}
