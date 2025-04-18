/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:50:58 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/17 04:50:59 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
#define PARSER_H

#include "types.h"
#include <stdbool.h>

// HERE_DOC
int heredoc_handle(t_token *tokens);
char    *generate_temp_filename(void);

// EXPAND
char *check_expand(const char *input, t_quote_type quote);
void expand_handle(t_token *tokens);

// PARSER
t_command *parse_commands(t_token *tokens);
void print_commands(t_command *cmd_list);


/*Gestion des erreurs :*/
/*Si une redirection est présente sans token associé pour la cible (fichier ou délimiteur), il faut générer une erreur syntaxique similaire à bash.*/
/**/
/*Fusion des tokens successifs :*/
/*Parfois, des tokens T_WORD consécutifs pourraient être fusionnés, notamment s’ils résultent d’un découpage trop fin dans le lexer. */
/*Fais attention à bien distinguer un cas où l’espace est significatif (séparation d’arguments) ou non.*/
#endif
