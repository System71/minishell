/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:28:48 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:28:48 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/parsing_utils.h"
#include <unistd.h>
/***** strcmp *****/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;

	if (!s1 || !s2)
	{
		write(2, "Error : pointer NULL in ft_strncmp\n", 35);
		return (0);
	}
	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/***** strncmp *****/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	if (!s1 || !s2)
	{
		write(2, "Error : pointer NULL in ft_strncmp\n", 35);
		return (0);
	}
	if (n == 0)
		return (0);
	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && ss1[i] && ss2[i])
	{
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i < n)
		return (ss1[i] - ss2[i]);
	return (0);
}
