/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:52:21 by guroux            #+#    #+#             */
/*   Updated: 2019/04/16 14:38:53 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		freelist(t_dir *node)
{
	if (node)
	{

		if (node->name)
			ft_strdel(&(node->name));
		// if (node->groupname)
		// 	ft_strdel(&(node->groupname));
		// if (node->ownername)
		// 	ft_strdel(&(node->ownername));
		if (S_ISLNK(node->mode))
			ft_strdel(&(node->rpath));
		node->next = NULL;
		freelist(node->next);
		node->next = NULL;
		free(node);
		node = NULL;
	}
}
