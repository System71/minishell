/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/03 17:18:30 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_env(char **envp)
{
	char	**temp;
	int		len;

	temp = envp;
	len = 0;
	while (*temp)
	{
		len++;
		temp++;
	}
	return (len);
}
// A REVOIR ENTIEREMENT AVEC LES NOUVEAUX ARGUMENTS EN LISTE CHAINEE
int	export(char ***envp, char **full_cmd)
{
	char	**temp;
	char	**backup;
	int		len;
	int		i;

	len = get_len_env(*envp);
	temp = *envp;
	*envp = malloc(sizeof(char *) * (len + 2));
	if (!envp)
	{
		perror("malloc envp");
		exit(EXIT_FAILURE);
	}
	backup = *envp;
	i = 0;
	while (*temp)
	{
		**envp = strdup(*temp);
		printf("%s\n", **envp);
		(**envp)++;
		temp++;
	}
	**envp = strdup(*full_cmd);
	*envp = backup;
	return (1);
}

int	unset(char **envp, char **full_cmd)
{
	return (1);
}
