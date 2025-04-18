/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:35:12 by prigaudi          #+#    #+#             */
/*   Updated: 2024/11/20 18:33:51 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_malloc(char **split, int j)
{
	int	i;

	i = j - 1;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

static char	*extract(char const *s, int start, int end)
{
	int		i;
	char	*extracted_str;

	extracted_str = malloc(sizeof(char) * (end - start + 2));
	if (extracted_str == NULL)
		return (NULL);
	i = 0;
	while (i + start <= end)
	{
		extracted_str[i] = s[start + i];
		i++;
	}
	extracted_str[i] = '\0';
	return (extracted_str);
}

static int	char_count(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

static char	*test_str(char **split, int j)
{
	if (split[j] == NULL)
	{
		free_malloc(split, j);
		return (NULL);
	}
	return (split[j]);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		start;
	int		i;
	int		j;

	split = malloc(sizeof(char *) * (char_count(s, c) + 1));
	if (split == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
			split[j] = extract(s, start, i);
			if (test_str(split, j++) == NULL)
				return (NULL);
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
