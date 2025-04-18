/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:27:20 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 10:24:04 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	char	**paths;
	char	*substr;
	char	*extracted_path;

	while (*envp)
	{
		substr = ft_substr(*envp, 0, 5);
		if (!substr)
			return (NULL);
		if (ft_strncmp(substr, "PATH=", 5) == 0)
		{
			extracted_path = ft_substr(*envp, 5, ft_strlen(*envp));
			free(substr);
			break ;
		}
		free(substr);
		envp++;
	}
	paths = ft_split(extracted_path, ':');
	if (!paths)
		return (NULL);
	free(extracted_path);
	return (paths);
}

void	error_failure(char *arg, char *message)
{
	char	*full_message;

	full_message = ft_strjoin(arg, message);
	ft_putstr_fd(full_message, 2);
	free(full_message);
	exit(EXIT_FAILURE);
}

void	error(char *arg, char *message)
{
	char	*full_message;

	full_message = ft_strjoin(arg, message);
	ft_putstr_fd(full_message, 2);
	free(full_message);
}

void	free_split(char **split)
{
	char	**temp;

	temp = split;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(split);
}

void	free_child_struct(t_child child)
{
	if (child.pid)
		free(child.pid);
	if (child.status)
		free(child.status);
}
