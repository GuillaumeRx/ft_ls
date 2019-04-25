/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:08:40 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 22:41:01 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	int		minor;
	int		major;

	minor = minor(act->rdev);
	major = major(act->rdev);
	if (S_ISCHR(act->mode) || S_ISBLK(act->mode))
		printminmaj(size, minor, major);
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
	int		i;

	tmp = *start;
	tblocks = 0;
	i = 0;
	while (tmp != NULL)
	{
		i++;
		tblocks += tmp->blocks;
		tmp = tmp->next;
	}
	if (i > 0)
	{
		ft_putstr("total ");
		ft_putnbr(tblocks);
		ft_putchar('\n');
	}
}
