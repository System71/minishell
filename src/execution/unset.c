/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:57:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/10 16:34:47 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_forbidden_char_unset(char *variable_name)
{
	int	i;

	i = 0;
	while (variable_name[i])
	{
		if (i == 0 && !ft_isalpha(variable_name[i]) && variable_name[i] != '_')
			return (0);
		if (!ft_isalnum(variable_name[i]) && variable_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	compare_loop(char ***my_env, char *arg)
{
	char	*variable_to_add;
	char	*variable_to_compare;
	int		i;

	variable_to_add = extract_variable(arg);
	i = 0;
	while ((*my_env)[i])
	{
		variable_to_compare = extract_variable((*my_env)[i]);
		if (!variable_to_compare)
		{
			perror("malloc variable_to_compare");
			exit(EXIT_FAILURE);
		}
		if (!ft_strncmp(variable_to_add, variable_to_compare,
				ft_strlen(variable_to_compare)))
		{
			remove_variable(my_env, i);
			return (0);
		}
		i++;
	}
	return (0);
}

// remove variable if it exists
// check forbidden characters
static int	check_variable_unset(char ***my_env, char *arg)
{
	dprintf(2, "Test\n");
	if (*arg == '-')
	{
		triple_putstr_fd("export: ", ft_substr(arg, 0, 2), ": invalid option\n",
			2);
		return (1);
	}
	if (!check_forbidden_char_unset(arg))
	{
		triple_putstr_fd("export: ", arg, ": not a valid identifier\n", 2);
		return (1);
	}
	return (compare_loop(my_env, arg));
}

int	unset(char ***my_env, char **args)
{
	char	*variable_to_compare;
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		if (check_variable_unset(my_env, args[i]))
			return (1);
		j = 0;
		while ((*my_env)[j])
		{
			variable_to_compare = extract_variable((*my_env)[j]);
			if (!ft_strncmp(args[i], (*my_env)[j], ft_strlen(args[i])))
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
