/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 05:00:56 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/16 05:01:48 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

static void	free_tab_partial(char **dup, int until)
{
	while (--until >= 0)
		free(dup[until]);
	free(dup);
}

static int	tab_count(char **tab)
{
	int	count;

	count = 0;
	while (tab && tab[count])
		count++;
	return (count);
}

char	**ft_strdup_tab(char **tab)
{
	char	**dup;
	int		count;
	int		i;

	count = tab_count(tab);
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
		{
			free_tab_partial(dup, i);
			return (NULL);
		}
		i++;
	}
	dup[count] = NULL;
	return (dup);
}
