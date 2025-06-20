/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/19 20:18:23 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(const char *input, t_env *my_env)
{
	t_token		*tokens;
	t_command	*cmd_list;

	tokens = lexer(input);
	print_tokens(tokens);
	if (!check_syntax(tokens, my_env))
	{
		mem_free_all(8);
		return (NULL);
	}
	tokens = group_tokens(tokens);
	print_tokens(tokens);
	heredoc_handle(tokens, my_env);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		mem_free_all(8);
		return (NULL);
	}
	expand_handle(tokens, my_env);
	print_tokens(tokens);
	split_handle(tokens);
	print_tokens(tokens);
	cmd_list = parse_commands(tokens);
	print_commands(cmd_list);
	return (cmd_list);
}
