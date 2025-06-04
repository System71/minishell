/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:42:21 by okientzl          #+#    #+#             */
/*   Updated: 2025/06/04 15:08:22 by prigaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

static t_mem_node	**get_mem_list(void)
{
	static t_mem_node	*head = NULL;

	return (&head);
}

void	mem_register(void *ptr)
{
	t_mem_node	*node;
	t_mem_node	**head;

	head = get_mem_list();
	node = malloc(sizeof *node);
	if (node == NULL)
	{
		perror("minishell: malloc");
		mem_free_all();
		exit(EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->next = *head;
	*head = node;
}

void	mem_free_all(void)
{
	t_mem_node	*cur;
	t_mem_node	*tmp;
	t_mem_node	**head;

	head = get_mem_list();
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

void	*ft_xmalloc(int size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
	{
		perror("minishell: malloc");
		mem_free_all();
		exit(EXIT_FAILURE);
	}
	mem_register(p);
	return (p);
}
