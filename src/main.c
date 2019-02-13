/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:44:46 by guroux            #+#    #+#             */
/*   Updated: 2019/02/13 13:03:27 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_opt	*opt;
	int		i;

	i = 1;
	opt = (t_opt *)malloc(sizeof(t_opt));
	if (ac > 1)
	{
		while (i < ac)
		{
			if (av[i][0] == '-' && av[i][1] != '-')
			{
				setopt(av[i], opt);
				i++;
			}
			else
				break ;
		}
		while (i < ac)
		{
			parsedir(av[i], opt);
			i++;
		}
		if (i == ac)
			parsedir(".", opt);
	}
	else
		parsedir(".", opt);
	return (0);
}
