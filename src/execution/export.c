/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/13 10:33:34 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_forbidden_char_export(char *variable_name)
{
	int	i;

	i = 0;
	printf("variable name=%s\n", variable_name);
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

static int	compare_loop(char ***my_env, char *arg)
{
	char	*variable_to_add;
	char	*variable_to_compare;
	int		i;

	variable_to_add = extract_variable(arg);
	printf("variable to add=%s\n", variable_to_add);
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
static int	check_variable_export(char ***my_env, char *arg)
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

static int	env_loop(char ***my_env, char **temp, char **args, int i, int len)
{
	int	j;

	j = 0;
	while (j < len)
	{
		(*my_env)[j] = strdup(temp[j]);
		if (!(*my_env)[j])
		{
			perror("malloc *my_env");
			exit(EXIT_FAILURE);
		}
		j++;
	}
	(*my_env)[j] = strdup(args[i]);
	if (!(*my_env)[j])
	{
		perror("malloc *my_env");
		exit(EXIT_FAILURE);
	}
	j++;
	(*my_env)[j] = NULL;
	return (0);
}

static void	display_export(char ***my_env)
{
	int	i;

	i = 0;
	while ((*my_env)[i])
	{
		ft_putstr_fd((*my_env)[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	export(char ***my_env, char **args)
{
	char	**temp;
	int		len;
	int		i;

	if (!args[1])
		display_export(my_env);
	else
	{
		i = 0;
		while (args[++i])
		{
			if (check_variable_export(my_env, args[i]))
				return (1);
			temp = *my_env;
			len = get_len_env(*my_env);
			*my_env = malloc(sizeof(char *) * (len + 2));
			if (!*my_env)
			{
				perror("malloc envp");
				exit(EXIT_FAILURE);
			}
			env_loop(my_env, temp, args, i, len);
		}
	}
	return (0);
}
