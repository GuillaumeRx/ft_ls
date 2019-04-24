/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 14:51:43 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parsemode(mode_t mode)
{
	if (S_ISREG(mode))
		ft_putchar('-');
	else if (S_ISDIR(mode))
		ft_putchar('d');
	else if (S_ISLNK(mode))
		ft_putchar('l');
	else if (S_ISCHR(mode))
		ft_putchar('c');
	else if (S_ISFIFO(mode))
		ft_putchar('p');
	else if (S_ISSOCK(mode))
		ft_putchar('s');
	else if (S_ISBLK(mode))
		ft_putchar('b');
}

void	printdate(time_t rawtime)
{
	time_t		now;
	char		*dyear;
	char		*dnbr;
	char		*dmonth;
	char		*dtime;

	now = time(NULL);
	ft_putstr(dmonth = ft_strsub(ctime(&rawtime), 4, 3));
	ft_putchar(' ');
	ft_putstr(dnbr = ft_strsub(ctime(&rawtime), 8, 2));
	ft_putchar(' ');
	if ((now - rawtime) > 15780000)
	{
		ft_putstr(dyear = ft_strsub(ctime(&rawtime), 19, 5));
		ft_strdel(&dyear);
	}
	else
	{
		ft_putstr(dtime = ft_strsub(ctime(&rawtime), 11, 5));
		ft_strdel(&dtime);
	}
	ft_strdel(&dmonth);
	ft_strdel(&dnbr);
}

void	printowner(t_dir **start, char *owner)
{
	t_dir		*tmp;
	size_t		longer;

	tmp = *start;
	longer = 0;
	while (tmp != NULL)
	{
		if (longer < ft_strlen(tmp->ownername))
			longer = ft_strlen(tmp->ownername);
		tmp = tmp->next;
	}
	ft_putchar(' ');
	ft_putstr(owner);
	while (longer - ft_strlen(owner) != 0)
	{
		ft_putchar(' ');
		longer--;
	}
}

void	printgroup(t_dir **start, char *group)
{
	t_dir		*tmp;
	size_t		longer;

	tmp = *start;
	longer = 0;
	while (tmp != NULL)
	{
		if (longer < (ft_strlen(tmp->groupname) - 1))
			longer = ft_strlen(tmp->groupname) - 1;
		tmp = tmp->next;
	}
	ft_putchar(' ');
	ft_putstr(group);
	while (longer - (ft_strlen(group) - 1) != 0)
	{
		ft_putchar(' ');
		longer--;
	}
}

void	displaycontent(t_dir **start, t_opt *opt)
{
	t_dir *tmp;

	tmp = *start;
	if (opt->lst == 1)
		displaylong(start);
	else
	{
		while (tmp != NULL)
		{
			ft_putendl(tmp->name);
			tmp = tmp->next;
		}
	}
}
