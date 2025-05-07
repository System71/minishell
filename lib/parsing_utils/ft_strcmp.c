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
