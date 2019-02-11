/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/02/11 20:37:09 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*addnode(t_dir **head, struct dirent *dir)
{
	t_dir *last;
	t_dir *node;

	if (!(node = (t_dir *)malloc(sizeof(t_dir))))
		return (NULL);
	last = (*head);
	node->name = dir->d_name;
	node->type = dir->d_type;
	node->next = NULL;
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
	return (node);
}

int		parsedir(char *path, t_dir **node)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_dir			*tmp;
	t_dir			*act;
	char			*fullpath;

	if (*node == NULL)
	{
		tmp = (t_dir *)malloc(sizeof(*tmp));
		tmp->name = path;
		tmp->next = NULL;
	}
	else
		tmp = *node;
	tmp->content = NULL;
	if (!(dirp = opendir(path)))
		return (0);
	while ((dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dir->d_name, ".") != 0
		&& ft_strcmp(dir->d_name, "..") != 0 && dir->d_name[0] != '.')
		{
			if (!(act = addnode(&(tmp->content), dir)))
				return (0);
			if (dir->d_type == DT_DIR)
			{
				if (path[0] != '.')
				{
					fullpath = ft_strjoin(path, "/");
					fullpath = ft_strjoin(fullpath, dir->d_name);
					act->name = fullpath;
				}
				else
					fullpath = dir->d_name;
				if (!(parsedir(fullpath, &act)))
					return (0);
			}
		}
	}
	(*node) = tmp;
	return (1);
}
