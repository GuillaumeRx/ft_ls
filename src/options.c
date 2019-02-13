/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:50:38 by guroux            #+#    #+#             */
/*   Updated: 2019/02/13 18:05:51 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		setopt(char *entry, t_opt *opt)
{
	int i;

	i = 1;
	while (entry[i] != '\0')
	{
		if (entry[i] == 'R')
			opt->rec = 1;
		else if (entry[i] == 'l')
			opt->lst = 1;
		else if (entry[i] == 'a')
			opt->all = 1;
		else if (entry[i] == 'r')
			opt->rev = 1;
		else if (entry[i] == 't')
			opt->tim = 1;
		else
			return (0);
		i++;
	}
	return (1);
}
