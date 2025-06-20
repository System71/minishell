/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:37:28 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 18:15:49 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_export(char ***my_env)
{
	int	i;

	i = 0;
	while ((*my_env)[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd((*my_env)[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static bool is_in_env(char *env_name, char **my_env)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(env_name);
	while (my_env[i])
	{
		if (ft_strncmp(my_env[i], env_name, name_len) == 0
			&& my_env[i][name_len] == '=')
		{
			return (true);
		}
		i++;
	}
	printf("helo\n");
	return (false);
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
			if (ft_strchr(args[i], '=') == NULL && is_in_env(args[i], *my_env))
				continue ;
			if (check_variable_export(my_env, args[i]))
				return (1);
			temp = *my_env;
			len = get_len_env(*my_env);
			*my_env = ft_xmalloc(sizeof(char *) * (len + 2), 60);
			env_loop(my_env, temp, args, i);
		}
	}
	return (0);
}
