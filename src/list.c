/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:52:21 by guroux            #+#    #+#             */
/*   Updated: 2019/04/29 19:31:05 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		freelist(t_dir **lst, t_opt *opt)
{
	if (*lst)
	{
		freelist(&((*lst)->next), opt);
		ft_strdel(&((*lst)->name));
		if (opt->lst == 1 || opt->tim == 1)
		{
			ft_strdel(&((*lst)->groupname));
			ft_strdel(&((*lst)->ownername));
			if (S_ISLNK((*lst)->mode))
				ft_strdel(&((*lst)->rpath));
		}
		free(*lst);
		*lst = NULL;
	}
}
