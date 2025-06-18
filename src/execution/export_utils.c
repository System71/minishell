/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:42:13 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/18 14:47:43 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_forbidden_char_export(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (i == 0 && !ft_isalpha(variable[i]) && variable[i] != '_')
			return (0);
		if (variable[i] == '=')
			return (1);
		if (!ft_isalnum(variable[i]) && variable[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// remove variable if it exists
// check forbidden characters
int	check_variable_export(char ***my_env, char *arg)
{
	if (*arg == '-')
	{
		triple_putstr_fd("export: ", ft_substr(arg, 0, 2), ": invalid option\n",
			2);
		return (1);
	}
	if (!check_forbidden_char_export(arg))
	{
		triple_putstr_fd("export: ", arg, ": not a valid identifier\n", 2);
		return (1);
	}
	return (compare_loop(my_env, arg));
}

int	env_loop(char ***my_env, char **temp, char **args, int i)
{
	int	j;
	int	len;

	len = get_len_env(temp);
	j = 0;
	while (j < len)
	{
		(*my_env)[j] = ft_strdup_oli(temp[j], 60);
		j++;
	}
	(*my_env)[j] = ft_strdup_oli(args[i], 60);
	j++;
	(*my_env)[j] = NULL;
	return (0);
}
