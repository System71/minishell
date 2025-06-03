/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:50:58 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/28 17:01:28 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <stdbool.h>

// HERE_DOC
int			heredoc_handle(t_token *tokens, t_env *my_env);
char		*generate_temp_filename(void);

// EXPAND
char		*check_expand(const char *input, t_quote_type quote,
				t_token *current, t_env *my_env);
void		expand_handle(t_token *tokens, t_env *my_env);
int			append_str(char **dest, const char *src);
char		*concat_segments(t_token *token);
void	init_expand_handle(t_expand_handle *handle, t_token *tokens);
char *ft_getenv(char *name, t_env *my_env);

// SPLIT_TOKEN
void		split_handle(t_token *tok_list);

// PARSER
t_command	*parse_commands(t_token *tokens);
bool		is_redirection_type(t_token_type type);
void		append_arg_to_command(t_command *cmd, char *arg);
t_command	*init_or_get_current_command(t_command **cmd_list,
				t_command *current_cmd);
// DEBUG
void		print_commands(t_command *cmd_list);

#endif
