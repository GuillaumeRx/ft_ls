/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/02/07 19:20:28 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parsedir(char *path, t_dir *node)
{
	DIR				*dirp;
	struct dirent	*dirc;
	t_dir			*content;
	t_dir			*tmp = NULL;

	if (!(dirp = opendir(path)))
			return (0);
	if (node == NULL)
	{
		if(!(node = (t_dir *)malloc(sizeof(t_dir))))
			return (0);
		node->next = NULL;
	}
	content = tmp;
	while ((dirc = readdir(dirp)) != NULL)
	{
		if ((ft_strcmp(dirc->d_name, ".") != 0) && (ft_strcmp(dirc->d_name, "..") != 0))
		{
			tmp = (t_dir *)malloc(sizeof(t_dir));
			tmp->name = ft_strdup(dirc->d_name);
			tmp->type = dirc->d_type;
			if (tmp->type == DT_DIR)
				parsedir(tmp->name, tmp);
			tmp->next = NULL;
			tmp = tmp->next;
		}
	}
	node->content = content;
	return (1);
}
