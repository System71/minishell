/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okientzl <okientzl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:42:21 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/06 10:38:15 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_free_loop(char *input)
{
	free(input);
	mem_free_all(8);
}

static t_mem_node	**get_mem_list(int which_list)
{
	static t_mem_node	*heart = NULL;
	static t_mem_node	*loop = NULL;

	if (which_list == 60)
		return (&heart);
	if (which_list == 8)
		return (&loop);
	return (NULL);
}

void	mem_register(void *ptr, int which_list)
{
	t_mem_node	*node;
	t_mem_node	**head;

	head = get_mem_list(which_list);
	node = malloc(sizeof * node);
	if (node == NULL)
	{
		perror("minishell: malloc");
		mem_free_all(60);
		mem_free_all(8);
		exit(EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
}

void	mem_free_all(int which_list)
{
	t_mem_node	*cur;
	t_mem_node	*tmp;
	t_mem_node	**head;

	head = get_mem_list(which_list);
	cur = *head;
	while (cur)
	{
		free(cur->ptr);
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	*head = NULL;
}

void	*ft_xmalloc(int size, int which_list)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
	{
		perror("minishell: malloc");
		mem_free_all(60);
		mem_free_all(8);
		exit(EXIT_FAILURE);
	}
	mem_register(p, which_list);
	return (p);
}
