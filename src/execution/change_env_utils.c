/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:18:10 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 17:35:47 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_forbidden_char_export(char *variable_name)
{
	int	i;

	i = 0;
	while (variable_name[i])
	{
		if (i == 0 && !ft_isalpha(variable_name[i]) && variable_name[i] != '_')
			return (0);
		if (variable_name[i] == '=')
			return (1);
		if (!ft_isalnum(variable_name[i]) && variable_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_len_env(char **my_env)
{
	int	len;

	len = 0;
	while (my_env[len])
		len++;
	return (len);
}

int	variable_match(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] != '=' && b[i] != '=')
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return ((a[i] == '=' || a[i] == '\0') && (b[i] == '=' || b[i] == '\0'));
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
