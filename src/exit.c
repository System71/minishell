/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/04 09:12:27 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "memory/mem.h"

void	exit_shell(void)
{
	ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	mem_free_all(60);
	exit(0);
}

int	exit_failure(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	return (1);
}
// ??????????????????
static int	code_is_digit(char *code)
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

static int	get_error_code(int code)
{
	if (code > 255)
	{
		code = code % 256;
		return (code);
	}
	if (code < 0)
	{
		code = 256 - (-code % 256);
		return (code);
	}
	return (code);
}

int	my_exit(char **args)
{
	int	error_code;

	if (!args[1])
		exit(EXIT_SUCCESS);
	if (!code_is_digit(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(2);
	}
	else
	{
		error_code = get_error_code(ft_atoi(args[1]));
		exit(error_code);
	}
}
