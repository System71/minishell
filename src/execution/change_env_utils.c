/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:18:10 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 14:47:25 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
