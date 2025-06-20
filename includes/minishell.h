/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:21:36 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/20 07:35:08 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# define INITIAL_BUFFER_SIZE 64
# define BUFFER_SIZE 1024
# define BUF_SIZE 256
# define BASE "/tmp/heredoc_"
# define RANDOM_BYTES 8
# define MAX_TRY 100

# include "libft.h"
# include "types.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// ========== MAIN ==========
t_env							*init_minishell(char **envp);
void							execute_and_cleanup(t_command *cmd_list,
									t_env *my_env);

// ========== NEW_PIPEX ==========
void							new_pipex(t_command *current, t_env *my_env);
void							execute_command(char **s_cmd, char **env);

// ========== NEW_PIPEX_UTILS ==========
int								init_redirections(t_infileoutfile *redir);
void							close_all(t_infileoutfile *redirections);
void							close_pipefd(int pipefd[2]);
int								get_redirection(t_command *current,
									t_infileoutfile *redirections,
									t_env *my_env);

// ========== MULTI_COMMAND_UTILS ==========
void							mem_free_alls(void);
void							wait_loop(t_command *current, t_env *my_env);
void							child(t_command *current, int pipefd[2],
									int prev_fd, t_env *my_env);

// ========== GET_REDIRECTION_UTILS ==========
void							restore_std(t_infileoutfile *redirections);
int								redir_in(t_command *current,
									t_infileoutfile *redirections,
									t_env *my_env);
int								redir_out(t_command *current, int *outfile,
									t_env *my_env);
int								redir_out_append(t_command *current,
									int *outfile, t_env *my_env);

// ========== BUILTIN ==========
int								pwd(char **args);
int								echo(char **args);
int								env(char ***my_env);

// ========== EXIT ==========
void							my_exit(char **args,
									t_infileoutfile *redirections,
									t_env *my_env);
void							exit_shell(t_env *my_env);

// ========== EXPORT ==========
int								export(char ***my_env, char **args);

// ========== EXPORT UTILS ==========
int								check_forbidden_char_export(char *variable);
int								check_variable_export(char ***my_env,
									char *arg);
int								env_loop(char ***my_env, char **temp,
									char **args, int i);

// ========== UNSET ==========
int								unset(char ***my_env, char **args);

// ========== CHANGE_ENV UTILS ==========
int								compare_loop(char ***my_env, char *arg);
void							free_both(char *s1, char *s2);
int								get_len_env(char **my_env);
char							*extract_variable(char *str);
int								remove_variable(char ***my_env, int position);

// ========== CD ==========
int								cd(t_env *my_env, char **full_cmd);
char							*get_oldpwd(t_env *my_env);
void							update_pwd_vars(char ***envp,
									const char *old_pwd);

// ========== CMD PROCESS ==========
int								is_builtin(t_env *my_env, t_command *current,
									t_infileoutfile *redirections);
void							cmd_not_built(t_env *my_env, char **args);

// ========== UTILS ==========
void							triple_putstr_fd(char *s1, char *s2, char *s3,
									int fd);
int								exit_failure(char *message);
char							**env_cpy(char **envp);
void							free_split(char **split);
void							eacces_exit(char *arg);

// ========== ERROR ==========
void							report_syntax_error(t_syntax_err err,
									const char *input);
bool							check_syntax(t_token *tokens, t_env *my_env);

// ========== DEBUG ==========
t_token_type					get_token_type(const char *str);
void							print_tokens(t_token *tokens);

// ========== MEMORY ==========
void							*ft_xmalloc(int size, int which_list);
void							mem_register(void *ptr, int which_list);
void							mem_free_all(int which_list);
void							ft_free_loop(char *input);
void							ft_free_double_tab(char **tab, char **tab_2);
void							ft_free_tab(char **tab, int out_or_not);

// ========== LEXER ==========
t_token							*lexer(const char *input);
t_command						*parse_input(const char *input, t_env *my_env);

// ========== CREATE_TOKEN ==========
t_token							*create_token_with_segment(const char *content,
									t_quote_type quote);
void							rebuild_segments(t_token *tok,
									const char *word);

// ========== TOKEN_LIST ==========
void							add_token_or_segment(t_token **tokens,
									const char *content, t_quote_type quote,
									bool mergeable);

// ========== SEGMENT ==========
void							add_segment_to_token(t_token *token,
									const char *content, t_quote_type quote);

// ========== LEXER_NORMAL ==========
void							process_normal_char(t_utils_lexer *storage,
									const char *input, t_token **tokens);
void							add_op_token(t_token **tokens,
									t_token_type type, const char *lexeme);

// ========== LEXER_FLUSH ==========
void							flush_buffer(t_utils_lexer *storage,
									t_token **tokens, bool mergeable);

// ========== LEXER_QUOTE ==========
void							enter_quote_state(t_utils_lexer *storage,
									t_token **tokens, t_lexer_state new_state,
									t_quote_type new_quote);
void							process_quote_char(t_utils_lexer *storage,
									t_token **tokens);

// ========== DYNAMIC_BUFFER ==========
t_dynamic_buffer				*init_dynamic_buffer(void);
int								append_char(t_dynamic_buffer *buf, char c);
void							free_dynamic_buffer(t_dynamic_buffer *buf);

// ========== GROUP_TOKENS ==========
bool							is_redirection_type(t_token_type type);
t_token							*group_tokens(t_token *tokens);
t_token_segment					*create_segment(const char *content,
									t_quote_type quote);

// ========== EXPAND ==========
char							*check_expand(const char *input,
									t_quote_type quote, t_token *current,
									t_env *my_env);
void							expand_handle(t_token *tokens, t_env *my_env);
int								append_str(char **dest, const char *src);
char							*concat_segments(t_token *token);
void							init_expand_handle(t_expand_handle *handle,
									t_token *tokens);
char							*ft_getenv(char *name, t_env *my_env);

// ========== SPLIT_TOKEN ==========
void							split_handle(t_token *tok_list);

// ========== PARSER ==========
t_command						*parse_commands(t_token *tokens);
bool							is_redirection_type(t_token_type type);
void							append_arg_to_command(t_command *cmd,
									char *arg);
t_command						*init_or_get_current_command(
									t_command **cmd_list,
									t_command *current_cmd);

// ========== DEBUG ==========
void							print_commands(t_command *cmd_list);

// ========== SIGNALS ==========
extern volatile sig_atomic_t	g_signal;
void							set_signals_interactive(void);
void							set_signals_heredoc(void);
void							set_signals_child(void);
void							set_signals_wait(void);

// ========== HEREDOC ==========
void							heredoc_handle(t_token *tokens, t_env *my_env);
int								append_heredoc_line(t_heredoc *hd,
									const char *line);
void							init_hd_struct(t_heredoc *hd, t_token *curr);
void							heredoc_storage(t_token *curr, t_heredoc hd);
char							*generate_temp_filename(void);
int								read_line_hook(void);
void							destroy_file_heredoc(t_command *cmd_list);
void							write_heredoc_to_file(const char *filename,
									const char *content);

// ========== PARSING_UTILS ==========
/***** is_ft *****/
int								ft_isalpha(int c);
int								ft_isdigit(int c);
int								ft_isalnum(int c);
int								ft_iswhitespace(int c);
bool							is_special_char(char c);
;
bool							is_redirect_without_word(t_token *cur);
bool							is_isolated_op(t_token *prev, t_token *cur);
bool							is_consecutive_pipes(t_token *prev,
									t_token *cur);
bool							is_pipe_at_edge(t_token *prev, t_token *cur);
bool							is_bonus_token(t_token *cur);

/***** conversion *****/
char							*ft_itoa(int n);

/***** get_size *****/
int								get_int_size(int n);
size_t							ft_strlen(const char *s);

/***** memory *****/
void							*ft_memcpy(void *dest, const void *src,
									size_t n);
void							*ft_realloc(void *ptr, size_t old_size,
									size_t new_size, int wich_list);

/***** string *****/
size_t							ft_strlcpy(char *dst, const char *src,
									size_t size);
int								ft_strcpy(char *dst, const char *src);
void							ft_strcat(char *dest, const char *src);
char							*ft_strchr(const char *s, int c);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strdup_oli(const char *s, int which_list);
char							*ft_strndup_oli(const char *s, size_t n,
									int which_list);
char							**ft_split_exec(char const *s, char c);

#endif
