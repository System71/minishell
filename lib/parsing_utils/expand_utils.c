/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:15:16 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/03 14:18:37 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/types.h"
#include "../../includes/parsing_utils.h"

char *ft_getenv(char *name, t_env *my_env)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);

    while (my_env->env[i])
    {
		if (ft_strncmp(my_env->env[i], name, name_len) == 0
			&& my_env->env[i][name_len] == '=')
		{
			return (my_env->env[i] + name_len + 1);
		}
		i++;
	}
    return ("");
}

void	init_expand_handle(t_expand_handle *handle, t_token *tokens)
{
	handle->current = tokens;
	handle->seg = NULL;
	handle->old = NULL;
	handle->can_expand = false;
	handle->had_dollar = false;
}
