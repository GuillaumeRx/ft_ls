/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:50:38 by guroux            #+#    #+#             */
/*   Updated: 2019/04/11 22:17:48 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		setopt(char *entry, t_opt *opt)
{
	int i;

	i = 1;
	opt->rec = 0;
	opt->lst = 0;
	opt->all = 0;
	opt->rev = 0;
	opt->tim = 0;
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
		i++;
	}
	return (1);
}
