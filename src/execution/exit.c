/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/17 17:37:18 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_exit_code(char *code)
{
	int	i;

	i = 0;
	if (code[0] == '-' || code[0] == '+')
		i++;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	format_exit_code(int code)
{
	if (code > 255)
		return (code % 256);
	if (code < 0)
		return (256 - ((-code) % 256));
	return (code);
}

static void	exit_numeric_error(char *arg)
{
	triple_putstr_fd("minishell: exit: ",
		arg, ": numeric argument required\n", 2);
	mem_free_all(8);
	mem_free_all(60);
	exit(2);
}

static int	too_many_args(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

int	my_exit(char **args)
{
	int	error_code;

	if (!args[1])
	{
		mem_free_all(8);
		mem_free_all(60);
		exit(EXIT_SUCCESS);
	}
	if (!is_numeric_exit_code(args[1]))
		exit_numeric_error(args[1]);
	if (args[2])
		return (too_many_args());
	error_code = format_exit_code(ft_atoi(args[1]));
	mem_free_all(8);
	mem_free_all(60);
	exit(error_code);
}
