/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:57:18 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 17:36:46 by okientzl         ###   ########.fr       */
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

int	unset(char ***my_env, char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (*args[i] == '-' || !check_forbidden_char_unset(args[i]))
		{
			triple_putstr_fd("unset:", args[i], ":not valid identifier\n", 2);
			i++;
			continue ;
		}
		j = 0;
		while ((*my_env)[j])
		{
			if (variable_match((*my_env)[j], args[i]))
			{
				remove_variable(my_env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
