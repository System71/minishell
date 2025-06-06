/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 07:02:17 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 07:05:16 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LEXER_H
# define LEXER_H

# define INITIAL_BUFFER_SIZE 64
# define BUFFER_SIZE 1024

# include "types.h"

// ERROR
void				report_syntax_error(t_syntax_err err, const char *input);
bool				check_syntax(t_token *tokens, t_env *my_env);

// DEBUG
t_token_type		get_token_type(const char *str);
void				print_tokens(t_token *tokens);

// LEXER
t_token				*lexer(const char *input);
t_command			*parse_input(const char *input, t_env *my_env);

// CREATE TOKEN
t_token				*create_token_with_segment(const char *content,
						t_quote_type quote);
void				rebuild_segments(t_token *tok, const char *word);

// TOKEN_LIST
void				add_token_or_segment(t_token **tokens, const char *content,
						t_quote_type quote, bool mergeable);

// SEGMENT
void				add_segment_to_token(t_token *token, const char *content,
						t_quote_type quote);

// LEXER_NORMAL
void				process_normal_char(t_utils_lexer *storage,
						const char *input, t_token **tokens);
void				add_op_token(t_token **tokens, t_token_type type,
						const char *lexeme);

// LEXER_FLUSH
void				flush_buffer(t_utils_lexer *storage, t_token **tokens,
						bool mergeable);

// LEXER_QUOTE
void				enter_quote_state(t_utils_lexer *storage, t_token **tokens,
						t_lexer_state new_state, t_quote_type new_quote);
void				process_quote_char(t_utils_lexer *storage,
						t_token **tokens);

// DYNAMIC_BUFFER
t_dynamic_buffer	*init_dynamic_buffer(void);
int					append_char(t_dynamic_buffer *buf, char c);
void				free_dynamic_buffer(t_dynamic_buffer *buf);

// GROUP_TOKENS
bool				is_redirection_type(t_token_type type);
t_token				*group_tokens(t_token *tokens);
t_token_segment		*create_segment(const char *content, t_quote_type quote);

#endif
