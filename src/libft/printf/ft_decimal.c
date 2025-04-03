/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:02:31 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/28 15:40:17 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr(int n, int fd)
{
	int	x;
	int	isneg;
	int	counter;

	counter = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		counter++;
		n = -n;
	}
	if (n > 9)
	{
		isneg = ft_putnbr(n / 10, fd);
		if (isneg == -1)
			return (-1);
		counter += isneg;
	}
	x = n % 10 + 48;
	if (write(fd, &x, 1) == -1)
		return (-1);
	return (counter + 1);
}

int	ft_decimal(int current_value)
{
	return (ft_putnbr(current_value, 1));
}
