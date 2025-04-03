/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 09:21:36 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 14:14:22 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# include "libft.h"
# include "pipex.h"
# include "signals.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	T_WORD,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_DOLLAR
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	t_token_type		type;
	char				**argv;
	int					argc;
	pid_t				pid;
	int					*status;
	struct s_command	*next;
}						t_command;

// ========== SIGNALS ==========
void					signals(void);

// ========== BUILTIN ==========
void					pwd(void);
void					echo(char **argv);
void					env(char **envp);
void					cd(char *full_cmd);
void					exit_minishell(void);

// ========== EXPORT ==========
void					export(char ***envp, char *str);
void					unset(char **envp, char **full_cmd);

// ========== CMD ==========
void					child(t_command *cmds, int pipefd[2], char **envp);

#endif
