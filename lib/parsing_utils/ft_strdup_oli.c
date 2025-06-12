/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:29:06 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:29:06 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***** strdup *****/
char	*ft_strdup_oli(const char *s, int which_list)
{
	size_t	len;
	char	*copy;

	if (!s)
	{
		write(2, "Error : pointer NULL in ft_strdup\n", 34);
		return (NULL);
	}
	len = ft_strlen(s);
	copy = ft_xmalloc((len + 1) * sizeof(char), which_list);
	ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}
