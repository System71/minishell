/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:18:10 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 18:04:45 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_loop(char ***my_env, char *arg)
{
	char	*variable_to_add;
	char	*variable_to_compare;
	int		i;

	variable_to_add = extract_variable(arg);
	i = -1;
	while ((*my_env)[++i])
	{
		variable_to_compare = extract_variable((*my_env)[i]);
		if (!variable_to_compare)
		{
			free(variable_to_add);
			exit(exit_failure("malloc variable_to_compare failed"));
		}
		if (!ft_strncmp(variable_to_add, variable_to_compare,
				ft_strlen(variable_to_compare)))
		{
			remove_variable(my_env, i);
			free_both(variable_to_add, variable_to_compare);
			return (0);
		}
		free(variable_to_compare);
	}
	free(variable_to_add);
	return (0);
}

void	free_both(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	get_len_env(char **my_env)
{
	int	len;

	len = 0;
	while (my_env[len])
		len++;
	return (len);
}

char	*extract_variable(char *str)
{
	char	*extracted_variable;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	extracted_variable = ft_substr(str, 0, i);
	return (extracted_variable);
}

int	remove_variable(char ***my_env, int position)
{
	char	**temp;
	int		len;
	int		i;
	int		j;

	temp = *my_env;
	len = get_len_env(temp);
	*my_env = ft_xmalloc(sizeof(char *) * len, 60);
	i = 0;
	j = -1;
	while (++j < len)
	{
		if (j != position)
		{
			(*my_env)[i] = ft_strdup_oli(temp[j], 60);
			i++;
		}
	}
	(*my_env)[i] = NULL;
	return (0);
}
