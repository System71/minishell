/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:23:29 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/19 20:05:22 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***** split helper functions *****/
static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*malloc_word(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)ft_xmalloc((len + 1) * sizeof(char), 8);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**do_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = (char **)ft_xmalloc((count_words(s, c) + 1) * sizeof(char *), 8);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = malloc_word(s, c);
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}

/***** ft_split *****/
char	**ft_split_exec(char const *s, char c)
{
	if (!s)
	{
		return (NULL);
	}
	return (do_split(s, c));
}
