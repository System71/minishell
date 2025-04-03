/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:01:49 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 08:48:52 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../includes/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_child
{
	pid_t	*pid;
	int		*status;
}			t_child;

typedef struct s_data
{
	char	**argv;
	char	**envp;
	int		input_file;
	int		output_file;
	int		argc;
	t_child	child;
}			t_data;

//========== UTILS ===========
void		error_failure(char *arg, char *message);
void		error(char *arg, char *message);
void		free_split(char **split);
char		**get_paths(char **envp);
void		free_child_struct(t_child child);
//========== CHILDREN ===========
void		first_children(t_data data, char *arg, int end[2], int prev_fd);
void		last_child(t_data data, char *arg, int end[2], int prev_fd);
//========== HEREDOC===========
void		heredoc_creation(t_data data);
void		heredoc_child1(t_data data, int end[2], char *arg);
void		heredoc_child2(t_data data, int end[2], char *arg);
t_child		heredoc_init_child_struct(void);
void		heredoc_waitpid(t_child child);
//========== CMD ===========
int			cmd_launcher(char **envp, char *cmd);

#endif