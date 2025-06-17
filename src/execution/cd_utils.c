/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:07:37 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/17 15:24:12 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// PATH_MAX [4096]
void	update_pwd_vars(char ***envp, const char *old_pwd)
{
	char	buf[4096];
	char	oldpwd_entry[4096 + 8];
	char	pwd_entry[4096 + 5];

	if (!getcwd(buf, 4096))
		return ;
	ft_strlcpy(oldpwd_entry, "OLDPWD=", 8);
	ft_strlcat(oldpwd_entry, old_pwd, sizeof(oldpwd_entry));
	ft_strlcpy(pwd_entry, "PWD=", 5);
	ft_strlcat(pwd_entry, buf, sizeof(pwd_entry));
	unset(envp, (char *[]){"unset", "OLDPWD", NULL});
	unset(envp, (char *[]){"unset", "PWD", NULL});
	export(envp, (char *[]){"export", oldpwd_entry, pwd_entry, NULL });
}

char	*get_home(t_env *my_env)
{
	int		i;
	char	*variable_name;

	i = 0;
	while ((*(my_env->env))[i])
	{
		variable_name = ft_substr((my_env->env)[i], 0, 5);
		if (!variable_name)
			exit_failure("error malloc variable_name", my_env, 0, NULL);
		if (!ft_strncmp(variable_name, "HOME=", 5))
		{
			free(variable_name);
			return (ft_strchr((my_env->env)[i], '=') + 1);
		}
		i++;
		free(variable_name);
	}
	return (NULL);
}
