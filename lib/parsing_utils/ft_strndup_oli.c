/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:04:51 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:19:53 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup_oli(const char *s, size_t n, int which_list)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = ft_xmalloc(len + 1, which_list);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
