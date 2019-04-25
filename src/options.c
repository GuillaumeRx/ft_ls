/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:50:38 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 22:17:48 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		setopt(char entry, t_opt *opt)
{
	if (entry == 'R')
		opt->rec = 1;
	else if (entry == 'l')
		opt->lst = 1;
	else if (entry == 'a')
		opt->all = 1;
	else if (entry == 'r')
		opt->rev = 1;
	else if (entry == 't')
		opt->tim = 1;
	else
		return (0);
	return (1);
}

int		parseopt(char *str, t_opt *opt)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && (setopt(str[i], opt)))
		i++;
	if (str[i] && str[1] != '-')
	{
		usage(str[i]);
		return (0);
	}
	return (1);
}
