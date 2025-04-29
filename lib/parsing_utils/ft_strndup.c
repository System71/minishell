/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:04:51 by okientzl          #+#    #+#             */
/*   Updated: 2025/04/22 11:06:18 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../src/memory/mem.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = ft_xmalloc(len + 1);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
