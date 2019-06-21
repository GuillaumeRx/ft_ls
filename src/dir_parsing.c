/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:27:46 by guroux            #+#    #+#             */
/*   Updated: 2019/06/21 16:28:16 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverseparse(int i, int ac, char **av, t_opt *opt)
{
	int j;
	int printname;

	j = (ac - 1);
	printname = 0;
	if (i != (ac - 1))
		printname = 1;
	while (j >= i)
	{
		if (j != ac)
			ft_putchar('\n');
		if (printname)
		{
			ft_putstr(av[j]);
			ft_putendl(" :");
		}
		dirhandler(av[j], opt);
		j--;
	}
}

void	simpleparse(int i, int ac, char **av, t_opt *opt)
{
	int j;
	int printname;

	j = i;
	printname = 0;
	if (i != (ac - 1))
		printname = 1;
	while (j < ac)
	{
		if (j != i)
			ft_putchar('\n');
		if (printname)
		{
			ft_putstr(av[j]);
			ft_putendl(" :");
		}
		dirhandler(av[j], opt);
		j++;
	}
}
