/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/27 11:02:15 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"
#include "../memory/mem.h"
#include <stdio.h>

t_command	*parse_input(const char *input, int error_code)
{
	t_token		*tokens;
	t_command	*cmd_list;

	tokens = lexer(input);
	if (!tokens)
	{
		mem_free_all();
		return (NULL);
	}
	if (!check_syntax(tokens))
	{
		mem_free_all();
		return (NULL);
	}
	tokens = group_tokens(tokens);
	heredoc_handle(tokens);
	expand_handle(tokens, error_code);
	split_handle(tokens);
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
