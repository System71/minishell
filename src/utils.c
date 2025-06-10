/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:15 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 14:34:25 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./memory/mem.h"
#include "minishell.h"

void	triple_putstr_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}

char	**env_cpy(char **envp)
{
	char	**cpy;
	int		envp_len;
	int		i;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	cpy = malloc(sizeof(char *) * (envp_len + 1));
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

// PASSAGE EN VOID A VOIR
int	exit_failure(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}
