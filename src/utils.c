/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:15 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/02 17:30:37 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./memory/mem.h"

char	**env_cpy(char **envp)
{
	char	**cpy;
	int		envp_len;
	int		i;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	cpy = ft_xmalloc(sizeof(char *) * (envp_len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < envp_len)
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
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

int	exit_failure(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}

void	free_all(char **paths, char **full_cmd, char *end_path)
{
	if (paths)
		free_split(paths);
	if (full_cmd)
		free_split(full_cmd);
	if (end_path)
		free(end_path);
}
