/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:56:15 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/20 14:56:15 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_paths_loop(t_env *my_env, char **extracted_path)
{
	char	*substr;
	int		i;

	i = -1;
	while ((my_env->env)[++i])
	{
		substr = ft_substr((my_env->env)[i], 0, 5);
		if (!substr)
			return (1);
		if (ft_strncmp(substr, "PATH=", 5) == 0)
		{
			*extracted_path = ft_substr((my_env->env)[i], 5,
					ft_strlen((my_env->env)[i]));
			if (!*extracted_path)
			{
				exit_failure("full_path malloc extracted_path");
				free(substr);
				return (1);
			}
			free(substr);
			break ;
		}
		free(substr);
	}
	return (0);
}

char	**get_paths(t_env *my_env)
{
	char	**paths;
	char	*extracted_path;

	extracted_path = NULL;
	if (get_paths_loop(my_env, &extracted_path))
	{
		free(extracted_path);
		return (NULL);
	}
	paths = ft_split_exec(extracted_path, ':');
	if (!paths)
	{
		free(extracted_path);
		return (NULL);
	}
	free(extracted_path);
	return (paths);
}
