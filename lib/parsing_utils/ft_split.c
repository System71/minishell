/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:23:29 by okientzl          #+#    #+#             */
/*   Updated: 2025/05/07 17:23:29 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h> 
#include <unistd.h> 
#include "../../includes/parsing_utils.h" 

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
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
	{
		write(2, "Error: Memory allocation failed in malloc_word\n", 47);
		return (NULL);
	}
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**free_all(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (NULL);
}

static char	**do_split(char const *s, char c)
{
	char	**result;
	int		i;

	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
	{
		write(2, "Error: Memory allocation failed in ft_split\n", 44);
		return (NULL);
	}
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = malloc_word(s, c);
			if (!result[i++])
				return (free_all(result, i - 1));
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
char	**ft_split(char const *s, char c)
{
	if (!s)
	{
		write(2, "Error: Input string is NULL in ft_split\n", 40);
		return (NULL);
	}
	return (do_split(s, c));
}
