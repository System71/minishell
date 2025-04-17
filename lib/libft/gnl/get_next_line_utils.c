/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:20:30 by prigaudi          #+#    #+#             */
/*   Updated: 2025/02/11 11:47:25 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char *s1, char *s2, int byte_nbr)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && byte_nbr == 0)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + byte_nbr + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] && j < byte_nbr)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
