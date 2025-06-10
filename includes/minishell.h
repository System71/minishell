/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:21:36 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 16:04:08 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "parsing_utils.h"
# include "signals.h"
# include "types.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// ========== NEW_PIPEX ==========
void	get_redirection(t_command *current, int *infile, int *outfile);
void	new_pipex(t_command *current, t_env *my_env);

// ========== BUILTIN ==========
int		pwd(char **args);
int		echo(char **args);
int		env(char ***my_env);

// ========== EXIT ==========
int		my_exit(char **args);

// ========== EXPORT ==========
int		export(char ***my_env, char **args);

// ========== UNSET ==========
int		unset(char ***my_env, char **args);

// ========== CHANGE_ENV UTILS ==========
int		get_len_env(char **my_env);
char	*extract_variable(char *str);
int		remove_variable(char ***my_env, int position);

// ========== CD ==========
int		cd(char ***my_env, char **full_cmd);

// ========== CMD PROCESS ==========
int		is_builtin(t_env *my_env, t_command *current);
int		cmd_not_built(char ***my_env, char **args);

// ========== UTILS ==========
void	triple_putstr_fd(char *s1, char *s2, char *s3, int fd);
int		exit_failure(char *message);
char	**env_cpy(char **envp);

#endif
