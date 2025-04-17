/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:44:46 by okientzl          #+#    #+#             */
/*   Updated: 2025/02/27 17:44:46 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lib_utils.h"
#include <unistd.h>
/***** strdup *****/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*copy;

	if (!s)
	{
		write(2, "Error : pointer NULL in ft_strdup\n", 34);
		return (NULL);
	}
	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (!copy)
	{
		write(2, "Error : Fail malloc in ft_strdup\n", 33);
		return (NULL);
	}
	ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}
