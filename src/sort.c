/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:09:57 by guroux            #+#    #+#             */
/*   Updated: 2019/02/13 20:05:55 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*listswitch(t_dir *l1, t_dir *l2)
{
	l1->next = l2->next;
	l2->next = l1;
	return (l2);
}

t_dir	*ft_alphasort(t_dir *start)
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
				if (ft_strcmp(next->name, next->next->name) > 0)
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

t_dir	*ft_lastmodsort(t_dir *start)
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
				if (next->rawtime < next->next->rawtime)
				{
					act->next = listswitch(next, next->next);
					changed = 1;
				}
				else if (next->rawtime == next->next->rawtime)
				{
					if (ft_strcmp(next->name, next->next->name) > 0)
					{
						act->next = listswitch(next, next->next);
						changed = 1;
					}
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

void	sortlist(t_dir **start, t_opt *opt)
{
	if (opt->tim)
		*start = ft_lastmodsort(*start);
	else
		*start = ft_alphasort(*start);
}
