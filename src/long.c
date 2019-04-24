/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:08:40 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 17:04:22 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (S_ISDIR(mode) && !(mode & S_IXUSR) && !(mode & S_IXGRP)
	&& (mode & S_ISVTX))
		ft_putchar('T');
	else if (S_ISDIR(mode) && (mode & S_IXUSR) && (mode & S_IXGRP)
	&& (mode & S_ISVTX))
		ft_putchar('t');
	else if (mode & S_IXOTH)
		ft_putchar('x');
	else
		ft_putchar('-');
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

void	printsize(t_dir *act, int size)
{
	int	minor;
	int major;
	int i;

	if (S_ISCHR(act->mode) || S_ISBLK(act->mode))
	{
		minor = minor(act->rdev);
		major = major(act->rdev);
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
	else
	{
		while (size - ft_count(act->size))
		{
			ft_putchar(' ');
			size--;
		}
		ft_putnbr(act->size);
	}
}

int		calcpadding(t_dir **start)
{
	t_dir	*tmp;
	int		longer;

	tmp = *start;
	longer = 0;
	while (tmp != NULL)
	{
		if (S_ISCHR(tmp->mode) || S_ISBLK(tmp->mode))
		{
			if (longer < 8)
				longer = 8;
		}
		else
		{
			if (longer < ft_count(tmp->size))
				longer = ft_count(tmp->size);
		}
		tmp = tmp->next;
	}
	return (longer);
}

void	calcblocks(t_dir **start)
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
