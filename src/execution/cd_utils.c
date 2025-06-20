/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 07:14:31 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/20 07:17:04 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_oldpwd(t_env *my_env)
{
	int		i;
	char	*variable_name;

	i = 0;
	while ((my_env->env)[i])
	{
		variable_name = ft_substr((my_env->env)[i], 0, 7);
		if (!variable_name)
			exit_failure("error malloc variable_name");
		if (!ft_strncmp(variable_name, "OLDPWD=", 7))
		{
			free(variable_name);
			return (ft_strchr((my_env->env)[i], '=') + 1);
		}
		i++;
		free(variable_name);
	}
	return (NULL);
}

void	update_pwd_vars(char ***envp, const char *old_pwd)
{
	char	buf[4096];
	char	oldpwd_entry[sizeof(buf)];
	char	pwd_entry[sizeof(buf)];

	if (!getcwd(buf, sizeof(buf)))
		return ;
	ft_strlcpy(oldpwd_entry, "OLDPWD=", sizeof(oldpwd_entry));
	ft_strlcat(oldpwd_entry, old_pwd, sizeof(oldpwd_entry));
	ft_strlcpy(pwd_entry, "PWD=", sizeof(pwd_entry));
	ft_strlcat(pwd_entry, buf, sizeof(pwd_entry));
	export(envp, (char *[]){"export", oldpwd_entry, pwd_entry, NULL});
}
