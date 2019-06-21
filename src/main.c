/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:44:46 by guroux            #+#    #+#             */
/*   Updated: 2019/06/21 16:30:39 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		timesort(const char *param1, const char *param2)
{
	struct stat pstat1;
	struct stat pstat2;

	if (lstat(param1, &pstat1) < 0)
		return (0);
	if (lstat(param2, &pstat2) < 0)
		return (1);
	if (pstat1.st_mtimespec.tv_sec < pstat2.st_mtimespec.tv_sec)
		return (1);
	else
		return (0);
}

void	sortargs(int i, int ac, char **av, int (*f)(const char *, const char *))
{
	int		j;
	char	*tmp;

	j = i;
	while (j < (ac - 1))
	{
		if (f(av[j], av[j + 1]) > 0)
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
	int printname;

	j = i;
	printname = 0;
	if (opt->tim == 1)
		sortargs(i, ac, av, &timesort);
	else
		sortargs(i, ac, av, &ft_strcmp);
	if (i != (ac - 1))
		printname = 1;
	if (opt->rev)
		reverseparse(i, ac, av, opt);
	else
		simpleparse(i, ac, av, opt);
}

int		handleargs(int ac, char **av, t_opt *opt)
{
	int i;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		if (av[i][1] == '-')
		{
			i++;
			break ;
		}
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
	t_opt *opt;

	if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
		return (0);
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
