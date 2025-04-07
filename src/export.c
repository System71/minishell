/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/04/07 18:07:44 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len_env(char **my_env)
{
	int	len;

	len = 0;
	while (my_env[len])
		len++;
	return (len);
}
// A REVOIR ENTIEREMENT AVEC LES NOUVEAUX ARGUMENTS EN LISTE CHAINEE
// On passe l'adresse de **my_env pour pouvoir le modifier
int	export(char ***my_env, char **full_cmd)
{
	char	**temp;
	int		len;
	int		i;

	temp = *my_env;
	len = get_len_env(*my_env);
	*my_env = malloc(sizeof(char *) * (len + 2));
	if (!*my_env)
	{
		perror("malloc envp");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		(*my_env)[i] = strdup(temp[i]);
		i++;
	}
	(*my_env)[i++] = strdup(full_cmd[1]);
	(*my_env)[i] = NULL;
	return (0);
}

int	unset(char ***my_env, char **full_cmd)
{
	int	i;

	(void)my_env;
	(void)full_cmd;
	i = 0;
	while ((*my_env)[i])
	{
		if (!ft_strncmp(full_cmd[1], (my_env)[i], ft_strlen(full_cmd[1])))
		{
			break ;
		}
		i++;
	}
	return (0);
}
