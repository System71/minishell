/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 13:12:20 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// On passe l'adresse de **my_env pour pouvoir le modifier
int	export(char ***my_env, char **full_cmd)
{
	char	**temp;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (full_cmd[i])
	{
		if (check_variable_export(my_env, full_cmd[i]))
			return (1);
		temp = *my_env;
		len = get_len_env(*my_env);
		*my_env = malloc(sizeof(char *) * (len + 2));
		if (!*my_env)
		{
			perror("malloc envp");
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (j < len)
		{
			(*my_env)[j] = strdup(temp[j]);
			j++;
		}
		(*my_env)[j++] = strdup(full_cmd[i]);
		(*my_env)[j] = NULL;
		i++;
	}
	return (0);
}

// Faire une modification de la fonction check variable qui doit etre different de celle d'export
int	unset(char ***my_env, char **full_cmd)
{
	char	*variable_to_compare;
	int		i;
	int		j;

	i = 0;
	while (full_cmd[i])
	{
		if (check_variable_unset(my_env, full_cmd[i]))
			return (1);
		j = 0;
		while ((*my_env)[j])
		{
			variable_to_compare = extract_variable((*my_env)[j]);
			if (!ft_strncmp(full_cmd[i], (*my_env)[j], ft_strlen(full_cmd[i])))
			{
				remove_variable(my_env, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}
