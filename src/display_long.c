/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:13:14 by guroux            #+#    #+#             */
/*   Updated: 2019/05/14 16:30:42 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parseright2(mode_t mode)
{
	ft_putchar((mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((mode & S_IWUSR) ? 'w' : '-');
	if (!(mode & S_IXUSR) && (mode & S_ISUID))
		ft_putchar('S');
	else if ((mode & S_IXUSR) && (mode & S_ISUID))
		ft_putchar('s');
	else if (mode & S_IXUSR)
		ft_putchar('x');
	else
		ft_putchar('-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	if (!(mode & S_IXGRP) && (mode & S_ISGID))
		ft_putchar('S');
	else if ((mode & S_IXGRP) && (mode & S_ISGID))
		ft_putchar('s');
	else if (mode & S_IXGRP)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	parseright(mode_t mode)
{
	parseright2(mode);
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (!(mode & S_IXUSR) && !(mode & S_IXGRP) && (mode & S_ISVTX))
		ft_putchar('T');
	else if ((mode & S_IXUSR) && (mode & S_IXGRP) && (mode & S_ISVTX))
		ft_putchar('t');
	else if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	printslink(t_dir *act)
{
	if (S_ISLNK(act->mode))
	{
		ft_putstr(" -> ");
		ft_putstr(act->rpath);
	}
}

void	printminmaj(int size, int minor, int major)
{
	int i;

	i = size - 8;
	while (i > 0)
	{
		ft_putchar(' ');
		i--;
	}
	i = 3 - ft_count(major);
	while (i > 0)
	{
		ft_putchar(' ');
		i--;
	}
	ft_putnbr(major);
	ft_putstr(", ");
	i = 3 - ft_count(minor);
	while (i > 0)
	{
		ft_putchar(' ');
		i--;
	}
	ft_putnbr(minor);
}

void	displaylong(t_dir **start)
{
	t_dir *tmp;

	tmp = *start;
	calcblocks(start);
	while (tmp != NULL)
	{
		parsemode(tmp->mode);
		parseright(tmp->mode);
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
