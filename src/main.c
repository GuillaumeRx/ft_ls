/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:44:46 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 18:18:14 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reverseparse(int i, int ac, char **av, t_opt *opt)
{
	int		j;

	j = ac - 1;
	while (j >= i)
	{
		dirhandler(av[j], opt);
		j--;
	}
}

int		main(int ac, char **av)
{
	t_opt	*opt;
	int		i;
	int		j;

	i = 1;
	j = 1;
	opt = (t_opt *)malloc(sizeof(t_opt));
	if (ac > 1)
	{
		if (i < ac && av[i][0] == '-')
		{
			while (av[i][j] && (setopt(av[i][j], opt)))
				j++;
			if (av[i][j] && av[i][1] != '-')
			{
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				ft_putchar_fd(av[i][j], 2);
				ft_putchar('\n');
				return (0);
			}
			j = 1;
			i++;
		}
		if (av[i])
			reverseparse(i, ac, av, opt);
		else
			dirhandler(".", opt);
	}
	else
		dirhandler(".", opt);
	free(opt);
	return (1);
}
