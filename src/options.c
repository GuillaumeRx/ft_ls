/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 21:50:38 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 17:27:53 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		setopt(char entry, t_opt *opt)
{
	opt->rec = 0;
	opt->lst = 0;
	opt->all = 0;
	opt->rev = 0;
	opt->tim = 0;

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
