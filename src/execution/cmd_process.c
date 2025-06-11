/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:50:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 15:43:58 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**get_paths(char **envp)
// {
// 	char	**paths;
// 	char	*substr;
// 	char	*extracted_path;

// 	while (*envp)
// 	{
// 		substr = ft_substr(*envp, 0, 5);
// 		if (!substr)
// 			return (NULL);
// 		if (ft_strncmp(substr, "PATH=", 5) == 0)
// 		{
// 			extracted_path = ft_substr(*envp, 5, ft_strlen(*envp));
// 			break ;
// 		}
// 		envp++;
// 	}
// 	paths = ft_split(extracted_path, ':');
// 	if (!paths)
// 		return (NULL);
// 	return (paths);
// }

// static void	exec_cmd(char **envp, char **paths, char **args, char *end_path)
// {
// 	char	*full_path;
// 	int		i;

// 	i = -1;
// 	while (paths[++i])
// 	{
// 		full_path = ft_strjoin(paths[i], end_path);
// 		if (!full_path)
// 			exit_failure("full_path malloc ft_strjoin");
// 		printf("%s\n", full_path);
// 		execve(full_path, args, envp);
// 		if (errno == EACCES)
// 		{
// 			triple_putstr_fd("minishell: ", args[0], ": Permission denied\n",
// 				2);
// 			exit(126);
// 		}
// 		// ATTENTION ON EXECUT PLUS LES FONCTION NON BUILT IN ON RENTRE ICI
// 		// car le premiere exeve n'a pas trouve ls vue que ce n est pas un absolute path
// 		if (errno == ENOENT)
// 		{
// 			triple_putstr_fd("minishell: ", args[0], ": Command not found\n",
// 				2);
// 			exit(127);
// 		}
// 	}
// }

// if execve doesnt work we return 127
// int	cmd_not_built(char ***my_env, char **args)
// {
// 	char	**paths;
// 	char	*end_path;

// 	execve(args[0], args, *my_env);
// 	printf("Erreur lors de execve : errno = %d\n", errno);
// 	if (errno == EACCES)
// 	{
// 		triple_putstr_fd("minishell: ", args[0], ": Permission denied\n", 2);
// 		exit(126);
// 	}
// 	paths = get_paths(*my_env);
// 	if (!paths)
// 		return (exit_failure("get_paths"));
// 	end_path = ft_strjoin("/", args[0]);
// 	if (!end_path)
// 		return (exit_failure("args malloc ft_strjoin"));
// 	exec_cmd(*my_env, paths, args, end_path);
// 	exit(127);
// }
// int	is_builtin(t_env *my_env, char **args)
// IL FAUT REFAIRE UN DUP2 APRES AVOIR ECRIT DANS LE FICHIER POUR REMETTER LE PROCESSUS PARENT SUR L'ENTREE STANDARD !!!!
int	is_builtin(t_env *my_env, t_command *current)
{
	if (!ft_strncmp(current->args[0], "echo", ft_strlen("echo") + 1))
		my_env->error_code = echo(current->args);
	else if (!ft_strncmp(current->args[0], "cd", ft_strlen("cd") + 1))
		my_env->error_code = cd(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "pwd", ft_strlen("pwd") + 1))
		my_env->error_code = pwd(current->args);
	else if (!ft_strncmp(current->args[0], "export", ft_strlen("export") + 1))
		my_env->error_code = export(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "unset", ft_strlen("unset") + 1))
		my_env->error_code = unset(&my_env->env, current->args);
	else if (!ft_strncmp(current->args[0], "env", ft_strlen("env") + 1))
		my_env->error_code = env(&my_env->env);
	else if (!ft_strncmp(current->args[0], "exit", ft_strlen("exit") + 1))
		my_env->error_code = my_exit(current->args);
	else
		return (-1);
	return (my_env->error_code);
}
