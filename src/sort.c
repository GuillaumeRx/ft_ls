/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:09:57 by guroux            #+#    #+#             */
/*   Updated: 2019/04/12 22:28:44 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*listswitch(t_dir *l1, t_dir *l2)
{
	l1->next = l2->next;
	l2->next = l1;
	return (l2);
}

int		alpha(t_dir *node)
{
	return (ft_strcmp(node->name, node->next->name) > 0 ? 1 : 0);
}

int		lastmod(t_dir *node)
{
	if (node->rawtime < node->next->rawtime)
		return (1);
	else if (node->rawtime == node->next->rawtime)
		if (ft_strcmp(node->name, node->next->name) > 0)
			return (1);
	return (0);
}

t_dir	*ft_sort(t_dir *start, int (*f)(t_dir *))
{
	t_dir	*next;
	t_dir	*act;
	t_dir	*top;
	int		changed;

	changed = 1;
	if (!(top = (t_dir *)malloc(sizeof(t_dir))))
		return (NULL);
	top->next = start;
	if (start != NULL && start->next != NULL)
	{
		while (changed)
		{
			changed = 0;
			act = top;
			next = top->next;
			while (next->next != NULL)
			{
				if (f(next))
				{
					act->next = listswitch(next, next->next);
					changed = 1;
				}
				act = next;
				if (next->next != NULL)
					next = next->next;
			}
		}
	}
	next = top->next;
	free(top);
	return (next);
}

void revlist(t_dir **start)
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
		curr->next  = prev;
		prev = curr;
		curr = next;
	}
	*start = prev;
}

void	sortlist(t_dir **start, t_opt *opt)
{
	if (opt->tim == 1)
		*start = ft_sort(*start, &lastmod);
	else
		*start = ft_sort(*start, &alpha);
	if (opt->rev == 1)
		revlist(start);
}
