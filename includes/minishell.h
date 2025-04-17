/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:21:36 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/16 14:43:32 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# include "lexer.h"
# include "lib_utils.h"
# include "libft.h"
# include "parser.h"
# include "pipex.h"
# include "signals.h"
# include "types.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


// ========== SIGNALS ==========
void	signals(void);

// ========== CMD PROCESS ==========
int		cmd_process(t_command *cmd, char ***my_env);
void	child(t_command *cmds, int pipefd[2], char **envp);

// ========== BUILTIN ==========
int		pwd(void);
int		echo(char **argv);
int		env(char ***my_env);
int		exit_minishell(void);

// ========== EXPORT ==========
int		export(char ***my_env, char **full_cmd);
int		unset(char ***my_env, char **full_cmd);

// ========== CD ==========
int		cd(char ***my_env, char **full_cmd);

// ========== CMD NOT BUILT ==========
int		cmd_not_built(char ***envp, char **full_cmd);

// ========== UTILS ==========
int		exit_failure(char *message);
void	free_all(char **paths, char **full_cmd, char *end_path);
void	free_split(char **split);
char	**env_cpy(char **envp);

#endif
