/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:50:40 by okientzl          #+#    #+#             */
/*   Updated: 2025/02/27 15:50:40 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lib_utils.h"
#include <unistd.h>

/***** itoa *****/
char	*ft_itoa(int n)
{
	char		*result;
	long int	ln;
	int			len;

	ln = n;
	len = get_int_size(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
	{
		write(2, "Error : Fail malloc ft_itoa\n", 28);
		return (NULL);
	}
	result[len] = '\0';
	if (ln < 0)
		ln = -ln;
	while (len--)
	{
		result[len] = ln % 10 + '0';
		ln = ln / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
