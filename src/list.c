/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:52:21 by guroux            #+#    #+#             */
/*   Updated: 2019/04/19 17:52:27 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void		freelist(t_dir *(*lst))
// {
// 	if ((*lst))
// 	{

// 		if ((*lst)->name)
// 			ft_strdel(&((*lst)->name));
// 		if ((*lst)->groupname)
// 			ft_strdel(&((*lst)->groupname));
// 		if ((*lst)->ownername)
// 			ft_strdel(&((*lst)->ownername));
// 		if (S_ISLNK((*lst)->mode))
// 			ft_strdel(&((*lst)->rpath));
// 		(*lst)->next = NULL;
// 		freelist((*lst)->next);
// 		(*lst)->next = NULL;
// 		free((*lst));
// 		(*lst) = NULL;
// 	}
// }

void		freelist(t_dir **lst)
{
	if (*lst)
	{
		freelist(&((*lst)->next));
		ft_strdel(&((*lst)->name));
		if ((*lst)->groupname)
			ft_strdel(&((*lst)->groupname));
		if ((*lst)->ownername)
			ft_strdel(&((*lst)->ownername));
		// if (S_ISLNK((*lst)->mode))
		// 	ft_strdel(&((*lst)->rpath));
		free(*lst);
		*lst = NULL;
	}
}
