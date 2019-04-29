/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:44:46 by guroux            #+#    #+#             */
/*   Updated: 2019/04/29 18:11:13 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sortargs(int i, int ac, char **av)
{
	int			j;
	char		*tmp;

	j = i;
	while (j < (ac - 1))
	{
		if (ft_strcmp(av[j], av[j + 1]) > 0)
		{
			tmp = av[j];
			av[j] = av[j + 1];
			av[j + 1] = tmp;
			j = i;
		}
		else
			j++;
	}
}

void	parsedirname(int i, int ac, char **av, t_opt *opt)
{
	int j;
	int	printname;

	j = i;
	printname = 0;
	sortargs(i, ac, av);
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

int		handleargs(int ac, char **av, t_opt *opt)
{
	int i;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		if (!(parseopt(av[i], opt)))
			return (0);
		i++;
	}
	if (av[i])
		parsedirname(i, ac, av, opt);
	else
		dirhandler(".", opt);
	return (1);
}

int		main(int ac, char **av)
{
	t_opt	*opt;

	opt = (t_opt *)malloc(sizeof(t_opt));
	opt->all = 0;
	opt->lst = 0;
	opt->rec = 0;
	opt->rev = 0;
	opt->tim = 0;
	if (ac > 1)
		handleargs(ac, av, opt);
	else
		dirhandler(".", opt);
	free(opt);
	return (1);
}
