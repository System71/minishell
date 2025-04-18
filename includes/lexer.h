/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:50:09 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/17 04:50:09 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
#define LEXER_H

#define INITIAL_BUFFER_SIZE 64
#define BUFFER_SIZE 1024

#include "types.h"

t_token_type		get_token_type(const char *str);
void				print_tokens(t_token *tokens);

// LEXER
t_token				*lexer(const char *input);

// LEXER UTILS
void				process_normal_char(t_utils_lexer *storage, const char *input, t_token **tokens);
void				process_quote_char(t_utils_lexer *storage, t_token **tokens);
int					is_special_char(char c);
t_token				*add_token(t_token **list, const char *content, t_quote_type quote, bool mergeable);
void				flush_buffer(t_utils_lexer *storage, t_token **tokens, bool mergeable);

// DYNAMIC_BUFFER
t_dynamic_buffer	*init_dynamic_buffer(void);
int					append_char(t_dynamic_buffer *buf, char c);
void				free_dynamic_buffer(t_dynamic_buffer *buf);

// GROUP_TOKENS
t_token 			*group_tokens(t_token *tokens);
t_token_segment		*create_segment(const char *content, t_quote_type quote);

#endif
