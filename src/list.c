/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:52:21 by guroux            #+#    #+#             */
/*   Updated: 2019/04/11 22:24:56 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		freelist(t_dir **node)
{
	if (*node)
	{
		freelist(&((*node)->next));
		free((*node)->name);
		free((*node)->groupname);
		free((*node)->ownername);
		if (S_ISLNK((*node)->mode))
			free((*node)->rpath);
		free(*node);
		node = NULL;
	}
}
