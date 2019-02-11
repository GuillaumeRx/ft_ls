/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/02/11 22:32:38 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	displaycontent(t_dir **start, t_opt *opt)
{
	t_dir *tmp;

	tmp = (*start)->content;
	while (tmp != NULL)
	{
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
	if (opt->rec)
	{
		ft_putchar('\n');
		tmp = (*start)->content;
		while (tmp != NULL)
		{
			if (tmp->type == DT_DIR)
			{
				ft_putstr("./");
				ft_putstr(tmp->name);
				ft_putendl(":");
				displaycontent(&tmp, opt);
			}
			tmp = tmp->next;
		}
	}
}
