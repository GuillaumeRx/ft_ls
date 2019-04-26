/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:44:46 by guroux            #+#    #+#             */
/*   Updated: 2019/04/26 17:36:39 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sortargs(int i, int ac, char **av)
{
	char *tmp;
	int	j;

	j = i;
	if (i - ac > 1)
	{
		while(j < ac - 2)
		{
			if (strcmp(av[j], av[j + 1]) > 0)
			{
				tmp = av[j];
				av[j] = av[j + 1];
				av[j + 1] = tmp;
				j = i;
			}
			j++;
		}
	}
}

void	reverseparse(int i, int ac, char **av, t_opt *opt)
{
	int		j;
	int		printname;

	printname = 0;
	j = ac - 1;

	if (j != i)
		printname = 1;
	sortargs(i, ac, av);
	while (j >= i)
	{
		if (j != ac - 1)
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
		while (i < ac && av[i][0] == '-')
		{
			if (!(parseopt(av[i], opt)))
				return (0);
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
