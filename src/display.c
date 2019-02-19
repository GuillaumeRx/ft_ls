/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/02/19 17:19:12 by guroux           ###   ########.fr       */
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
	ft_putchar((mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((mode & S_IROTH) ? 'r' : '-');
	ft_putchar((mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((mode & S_IXOTH) ? 'x' : '-');

}

void	printdate(time_t rawtime)
{
	time_t		now;
	char		*timestr;

	now = time(NULL);
	timestr = ctime(&rawtime);
	timestr = ft_strsub(timestr, 4, 12);
	ft_putstr(timestr);

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

void	displaylong(t_dir **start)
{
	t_dir *tmp;

	tmp = *start;
	while (tmp != NULL)
	{
		parsemode(tmp->mode);
		parseownerright(tmp->mode);
		printlink(start, tmp->n_link);
		ft_putchar(' ');
		ft_putstr(tmp->ownername);
		ft_putchar(' ');
		ft_putchar(' ');
		ft_putstr(tmp->groupname);
		printsize(start, tmp->size);
		ft_putchar(' ');
		printdate(tmp->rawtime);
		ft_putchar(' ');
		ft_putendl(tmp->name);
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
	ft_putchar('\n');
}
