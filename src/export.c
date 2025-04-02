/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/02 14:03:06 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_len_env(char **envp)
{
	int	len;

	len = 0;
	while (*envp)
	{
		len++;
		envp++;
	}
	return (len);
}

void	export(char ***envp, char *str)
{
	char	**temp;
	int		len;

	len = get_len_env(envp);
	*envp = malloc(sizeof(char *) * (len + 2));
	if (!envp)
	{
		perror("malloc envp");
		free(temp);
		exit(EXIT_FAILURE);
	}
	temp = *envp;
	while (*temp)
	{
		**envp = strdup(*temp);
		temp++;
		(*envp)++;
	}
	**envp = strdup(str);
	*envp = temp;
}
