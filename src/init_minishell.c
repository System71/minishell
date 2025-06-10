/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:31:39 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:55:47 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "memory/mem.h"

char	**env_cpy(char **envp)
{
	char	**cpy;
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	cpy = ft_xmalloc(sizeof(char *) * (len + 1), 60);
	i = 0;
	while (i < len)
	{
		cpy[i] = ft_strdup_oli(envp[i], 60);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

static t_env	*init_env(char **envp)
{
	t_env		*cpy_env;

	cpy_env = ft_xmalloc(sizeof(t_env), 60);
	cpy_env->env = env_cpy(envp);
	cpy_env->error_code = 0;
	return (cpy_env);
}

int	read_line_hook(void)
{
	return (0);
}

t_env	*init_minishell(char **envp)
{
	t_env	*my_env;

	my_env = init_env(envp);
	rl_event_hook = read_line_hook;
	return (my_env);
}
