/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:09:57 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 17:00:47 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*sortmerge(t_dir *node1, t_dir *node2, int (*f)(t_dir *, t_dir *))
{
	t_dir *result;

	result = NULL;
	if (node1 == NULL)
		return (node2);
	else if (node2 == NULL)
		return (node1);
	if (f(node1, node2))
	{
		result = node2;
		result->next = sortmerge(node1, node2->next, f);
	}
	else
	{
		result = node1;
		result->next = sortmerge(node1->next, node2, f);
	}
	return (result);
}

void	fbsplit(t_dir *source, t_dir **front, t_dir **back)
{
	t_dir	*fast;
	t_dir	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

void	ft_mergesort(t_dir **start, int (*f)(t_dir *, t_dir *))
{
	t_dir	*head;
	t_dir	*node1;
	t_dir	*node2;

	head = *start;
	if (head && head->next)
	{
		fbsplit(head, &node1, &node2);
		ft_mergesort(&node1, f);
		ft_mergesort(&node2, f);
		*start = sortmerge(node1, node2, f);
	}
}

void	revlist(t_dir **start)
{
	t_dir	*prev;
	t_dir	*curr;
	t_dir	*next;

	prev = NULL;
	curr = *start;
	next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*start = prev;
}

void	sortlist(t_dir **start, t_opt *opt)
{
	if (opt->tim == 1)
		ft_mergesort(start, &lastmod);
	else
		ft_mergesort(start, &alpha);
	if (opt->rev == 1)
		revlist(start);
}
