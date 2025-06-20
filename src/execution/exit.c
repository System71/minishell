/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:47:45 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/20 11:21:01 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exit_too_many(t_infileoutfile *redirections)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	close_all(redirections);
}

static void	exit_with_code(t_infileoutfile *redirections, int *error_code,
		char *arg)
{
	*error_code = get_error_code(ft_atoi(arg));
	close_all(redirections);
	mem_free_alls();
	exit(*error_code);
}

void	my_exit(char **args, t_infileoutfile *redirections, t_env *my_env)
{
	int	error_code;

	if (!args[1])
	{
		close_all(redirections);
		error_code = my_env->error_code;
		mem_free_alls();
		exit(error_code);
	}
	if (!code_is_digit(args[1]))
	{
		triple_putstr_fd("minishell: exit: ", args[1],
			": numeric argument required\n", 2);
		close_all(redirections);
		error_code = my_env->error_code;
		mem_free_alls();
		exit(2);
	}
	if (args[2])
		exit_too_many(redirections);
	else
		exit_with_code(redirections, &error_code, args[1]);
}
