/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/02/18 21:09:47 by guroux           ###   ########.fr       */
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
		ft_putstr(tmp->groupname);
		ft_putchar(' ');
		ft_putnbr(tmp->size);
		ft_putchar(' ');
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
}

void	displaycontent(t_dir **start)
{
	// t_dir *tmp;

	// tmp = *start;
	displaylong(start);
	// while (tmp != NULL)
	// {
	// 	ft_putendl(tmp->name);
	// 	tmp = tmp->next;
	// }
	ft_putchar('\n');
}
