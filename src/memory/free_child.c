/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 07:47:53 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/13 07:47:55 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab, int out_or_not)
{
	size_t	i;

	if (!tab)
	{
		ft_printf("ft_free_tab : tab NULL !\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	if (out_or_not == 1)
	{
		exit (EXIT_FAILURE);
	}
}

void	ft_free_double_tab(char **tab, char **tab_2)
{
	size_t	i;

	if (!tab || !tab_2)
	{
		ft_printf("ft_free_tab : tab NULL !\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	i = 0;
	while (tab_2[i])
	{
		free(tab_2[i]);
		i++;
	}
	free(tab_2);
	exit (EXIT_FAILURE);
}
