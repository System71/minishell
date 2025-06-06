/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:21:36 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/06 08:57:47 by okientzl         ###   ########.fr       */
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
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

t_env	*init_minishell(char **envp);

void	execute_and_cleanup(t_command *cmd_list, t_env *my_env);

// ========== NEW_PIPEX ==========
void	new_pipex(t_command *current, t_env *my_env);

// ========== BUILTIN ==========
int		pwd(char **args);
int		echo(char **argv);
int		env(char ***my_env);

// ========== EXIT ==========
int		my_exit(char **args);
void	exit_shell(void);
int	exit_failure(char *message);

// ========== EXPORT ==========
int		export(char ***my_env, char **full_cmd);
int		unset(char ***my_env, char **full_cmd);

// ========== CD ==========
int		cd(char ***my_env, char **full_cmd);

// ========== CMD PROCESS ==========
int		is_builtin(t_env *my_env, char **args);
int		cmd_not_built(char ***envp, char **full_cmd);

#endif
