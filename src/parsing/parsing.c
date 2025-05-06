/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:53:04 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/06 13:54:21 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/types.h"
#include "../../includes/lexer.h"
#include "../../includes/parser.h"
#include "../memory/mem.h"

t_command *parse_input(const char *input)
{
    t_token     *tokens;
    t_command   *cmd_list;

    // 1) Lexing
    tokens = lexer(input);
    if (!tokens)
    {
        mem_free_all();
        return (NULL);
    }
    // 2) Vérification de syntaxe
    if (!check_syntax(tokens))
    {
        mem_free_all();
        return (NULL);
    }
    // 3) Regroupement et pré‐traitements
    tokens = group_tokens(tokens);
    heredoc_handle(tokens);
    expand_handle(tokens);
    split_handle(tokens);

    // 4) Construction de la liste de commandes
    cmd_list = parse_commands(tokens);
    return (cmd_list);
}
/*printf("LEXER \n");*/
/*print_tokens(tokens);*/

/*printf("GROUP \n");*/
/*print_tokens(tokens);*/

/*printf("HEREDOC and EXPAND \n");*/
/*print_tokens(tokens);*/

/*printf("COMMANDE \n");*/
/*print_commands(cmd_list);*/
