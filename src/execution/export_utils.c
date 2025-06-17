/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:42:13 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 15:04:43 by prigaudi         ###   ########.fr       */
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

static void	free_both(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

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

int	env_loop(char ***my_env, char **temp, char **args, int i, int len)
{
	int	j;

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
