/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/02 19:39:42 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_input(const char *input, t_env *my_env)
{
	t_token		*tokens;
	t_command	*cmd_list;

	my_env->error_code = 0;
	tokens = lexer(input);
	if (!tokens || !check_syntax(tokens, my_env))
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
	print_tokens(tokens);

	expand_handle(tokens, my_env);
	split_handle(tokens);
	print_tokens(tokens);
	cmd_list = parse_commands(tokens);
	return (cmd_list);
}
// DEBUG FONCTION WITH PRINTF
/*t_command *parse_input(const char *input)*/
/*{*/
/*	t_token     *tokens;*/
/*	t_command   *cmd_list;*/
/**/
/*	tokens = lexer(input);*/
/*	printf("LEXER \n");*/
/*	print_tokens(tokens);*/
/*	if (!tokens)*/
/*	{*/
/*		mem_free_all();*/
/*		return (NULL);*/
/*	}*/
/*	if (!check_syntax(tokens))*/
/*	{*/
/*		mem_free_all();*/
/*		return (NULL);*/
/*	}*/
/*	tokens = group_tokens(tokens);*/
/*	printf("GROUP \n");*/
/*	print_tokens(tokens);*/
/*	heredoc_handle(tokens);*/
/*	expand_handle(tokens);*/
/*	split_handle(tokens);*/
/*	printf("HEREDOC and EXPAND \n");*/
/*	print_tokens(tokens);*/
/**/
/**/
/*	cmd_list = parse_commands(tokens);*/
/*	printf("COMMANDE \n");*/
/*	print_commands(cmd_list);*/
/*	return (cmd_list);*/
/*}*/
