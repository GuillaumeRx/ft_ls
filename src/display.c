/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/04/12 20:00:57 by guroux           ###   ########.fr       */
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

void	parseownerright(mode_t mode)
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
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	if (S_ISDIR(mode) && !(mode & S_IXUSR) && !(mode & S_IXGRP) && (mode & S_ISVTX))
		ft_putchar('T');
	else if (S_ISDIR(mode) && (mode & S_IXUSR) && (mode & S_IXGRP) && (mode & S_ISVTX))
		ft_putchar('t');
	else if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	printdate(time_t rawtime)
{
	time_t		now;
	char		*timestr;
	char		*dyear;
	char		*dnbr;
	char		*dmonth;
	char		*dtime;

	now = time(NULL);
	timestr = ctime(&rawtime);

	ft_putstr(dmonth = ft_strsub(timestr, 4, 3));
	ft_putchar(' ');
	ft_putstr(dnbr = ft_strsub(timestr, 8, 2));
	ft_putchar(' ');
	if ((now - rawtime) > 15780000)
	{
		ft_putstr(dyear = ft_strsub(timestr, 19, 5));
		ft_strdel(&dyear);
	}
	else
	{
		ft_putstr(dtime = ft_strsub(timestr, 11, 5));
		ft_strdel(&dtime);
	}
	ft_strdel(&dmonth);
	ft_strdel(&dnbr);

}

void	printlink(t_dir **start, nlink_t n_link)
{
	t_dir	*tmp;
	int		longer;

	tmp = *start;
	longer = 0;
	while (tmp != NULL)
	{
		if (longer < ft_count(tmp->n_link))
			longer = ft_count(tmp->n_link);
		tmp = tmp->next;
	}
	ft_putchar(' ');
	while (longer - ft_count(n_link) >= 0)
	{
		ft_putchar(' ');
		longer--;
	}
	ft_putnbr(n_link);
}

void	printsize(t_dir **start, off_t size)
{
	t_dir	*tmp;
	int		longer;

	tmp = *start;
	longer = 0;
	while (tmp != NULL)
	{
		if (longer < ft_count(tmp->size))
			longer = ft_count(tmp->size);
		tmp = tmp->next;
	}
	ft_putchar(' ');
	while (longer - ft_count(size) >= 0)
	{
		ft_putchar(' ');
		longer--;
	}
	ft_putnbr(size);
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

void		calcblocks(t_dir **start)
{
	t_dir	*tmp;
	int		tblocks;

	tmp = *start;
	tblocks = 0;
	while (tmp != NULL)
	{
		tblocks += tmp->blocks;
		tmp = tmp->next;
	}
	ft_putstr("total ");
	ft_putnbr(tblocks);
	ft_putchar('\n');
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
		printsize(start, tmp->size);
		ft_putchar(' ');
		printdate(tmp->rawtime);
		ft_putchar(' ');
		ft_putstr(tmp->name);
		if (S_ISLNK(tmp->mode))
		{
			ft_putstr(" -> ");
			ft_putstr(tmp->rpath);
		}
		ft_putchar('\n');
		tmp = tmp->next;
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
