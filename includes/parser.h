/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:50:58 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/29 18:00:14 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
#define PARSER_H

#include "types.h"
#include <stdbool.h>

// HERE_DOC
int			heredoc_handle(t_token *tokens);
char		*generate_temp_filename(void);

// EXPAND
char		*check_expand(const char *input, t_quote_type quote, t_token *current);
void		expand_handle(t_token *tokens);
int			append_str(char **dest, const char *src);

// SPLIT_TOKEN
void		split_handle(t_token *tok_list);

// PARSER
t_command	*parse_commands(t_token *tokens);	
bool		is_redirection_type(t_token_type type);
void		append_arg_to_command(t_command *cmd, char *arg);
t_command	*init_or_get_current_command(t_command **cmd_list,
                                               t_command  *current_cmd);
// DEBUG
void		print_commands(t_command *cmd_list);


/*Gestion des erreurs :*/
/*Si une redirection est présente sans token associé pour la cible (fichier ou délimiteur), il faut générer une erreur syntaxique similaire à bash.*/
/**/
/*Fusion des tokens successifs :*/
/*Parfois, des tokens T_WORD consécutifs pourraient être fusionnés, notamment s’ils résultent d’un découpage trop fin dans le lexer. */
/*Fais attention à bien distinguer un cas où l’espace est significatif (séparation d’arguments) ou non.*/
#endif
