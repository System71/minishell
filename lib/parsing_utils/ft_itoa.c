/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:22:41 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:22:41 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/parsing_utils.h"
#include "../../src/memory/mem.h"
#include <unistd.h>

/***** itoa *****/
char	*ft_itoa(int n)
{
	char		*result;
	long int	ln;
	int			len;

	ln = n;
	len = get_int_size(n);
	result = ft_xmalloc((len + 1) * sizeof(char));
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
