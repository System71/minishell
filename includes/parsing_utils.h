/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:35:51 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 14:10:32 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include "./types.h"

/***** is_ft *****/
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_iswhitespace(int c);
bool			is_special_char(char c);;
bool			is_redirect_without_word(t_token *cur);
bool			is_isolated_op(t_token *prev, t_token *cur);
bool			is_consecutive_pipes(t_token *prev, t_token *cur);
bool			is_pipe_at_edge(t_token *prev, t_token *cur);
bool			is_bonus_token(t_token *cur);

/***** conversion *****/
char			*ft_itoa(int n);

/***** get_size *****/
int				get_int_size(int n);
size_t			ft_strlen(const char *s);

/***** memory *****/
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/***** string *****/
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strcpy(char *dst, const char *src);
void			ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, size_t n);
char			**ft_split(char const *s, char c);

#endif
