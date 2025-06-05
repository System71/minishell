/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/05 11:37:04 by prigaudi         ###   ########.fr       */
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

static int	check_forbidden_char(char *variable_name)
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

// remove variable if it exists
// check forbidden characters
static int	check_variable(char ***my_env, char *full_cmd)
{
	char	*variable_to_add;
	char	*variable_to_compare;
	int		i;

	if (*full_cmd == '-')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(ft_substr(full_cmd, 0, 2), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (1);
	}
	if (!check_forbidden_char(full_cmd))
	{
		ft_putstr_fd("export : ", 2);
		ft_putstr_fd(full_cmd, 2);
		ft_putstr_fd(": not a valid identifier\n\n", 2);
		return (1);
	}
	variable_to_add = extract_variable(full_cmd);
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
	int		j;

	i = 0;
	while (full_cmd[i])
	{
		if (check_variable(my_env, full_cmd[i]))
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

int	unset(char ***my_env, char **full_cmd)
{
	char	*variable_to_compare;
	int		i;
	int		j;

	i = 0;
	while (full_cmd[i])
	{
		if (check_variable(my_env, full_cmd[i]))
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
