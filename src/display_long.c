/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:13:14 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 14:45:18 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	printslink(t_dir *act)
{
	if (S_ISLNK(act->mode))
	{
		ft_putstr(" -> ");
		ft_putstr(act->rpath);
	}
}

void	displaylong(t_dir **start)
{
	t_dir *tmp;

	tmp = *start;
	calcblocks(start);
	while (tmp != NULL)
	{
		parsemode(tmp->mode);
		parseownerright(tmp->mode);
		printlink(start, tmp->n_link);
		printowner(start, tmp->ownername);
		ft_putchar(' ');
		printgroup(start, tmp->groupname);
		ft_putstr("  ");
		printsize(tmp, calcpadding(start));
		ft_putchar(' ');
		printdate(tmp->rawtime);
		ft_putchar(' ');
		ft_putstr(tmp->name);
		printslink(tmp);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}
