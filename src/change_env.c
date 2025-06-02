/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/02 18:37:20 by prigaudi         ###   ########.fr       */
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

static char	*extract_variable(char *str)
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

static int	remove_variable(char ***my_env, int position)
{
	char	**temp;
	int		len;
	int		i;
	int		j;

	temp = *my_env;
	len = get_len_env(temp);
	*my_env = malloc(sizeof(char *) * len);
	if (!*my_env)
	{
		perror("malloc envp");
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = -1;
	while (++j < len)
	{
		if (j != position)
		{
			(*my_env)[i] = strdup(temp[j]);
			i++;
		}
	}
	(*my_env)[i] = NULL;
	return (0);
}

int	unset(char ***my_env, char **full_cmd)
{
	char	*variable_to_compare;
	int		i;

	if (full_cmd[1] && !ft_strncmp(full_cmd[1], "-", 1))
	{
		ft_putstr_fd("minishell: unset : ", 2);
		ft_putstr_fd(ft_substr(full_cmd[1], 0, 2), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	i = 0;
	while ((*my_env)[i])
	{
		variable_to_compare = extract_variable((*my_env)[i]);
		if (!ft_strncmp(full_cmd[1], (*my_env)[i], ft_strlen(full_cmd[1])))
		{
			remove_variable(my_env, i);
			return (0);
		}
		i++;
	}
	return (1);
}
// remove variable if it exists
static int	check_variable(char ***my_env, char **full_cmd)
{
	char	*variable_to_add;
	char	*variable_to_compare;
	int		i;

	if (!ft_isalpha(*full_cmd[1]))
	{
		ft_putstr_fd("export : not a valid identifier\n", 2);
		return (1);
	}
	variable_to_add = extract_variable(full_cmd[1]);
	i = 0;
	while ((*my_env)[i])
	{
		variable_to_compare = extract_variable((*my_env)[i]);
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

// On passe l'adresse de **my_env pour pouvoir le modifier
int	export(char ***my_env, char **full_cmd)
{
	char	**temp;
	int		len;
	int		i;

	if (check_variable(my_env, full_cmd))
		return (1);
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
