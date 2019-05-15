/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:08:08 by guroux            #+#    #+#             */
/*   Updated: 2019/05/15 16:55:47 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		adddata(t_dir *node, char *path)
{
	struct stat		buf;

	if ((lstat(path, &buf)) < 0)
	{
		return (throwerror(path));
	}
	node->rawtime = buf.st_mtime;
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
	node->blocks = buf.st_blocks;
	node->rdev = buf.st_rdev;
	if (!(node->ownername = getowner(buf.st_uid)))
		return (0);
	if (!(node->groupname = getgroup(buf.st_gid)))
		return (0);
	if (S_ISLNK(buf.st_mode))
	{
		node->rpath = (char *)malloc(sizeof(char) * 40);
		node->rpath[readlink(path, node->rpath, 39)] = '\0';
	}
	return (1);
}

t_dir	*dolist(t_dir **start, struct dirent *dir, char *path)
{
	t_dir	*node;

	if (!(node = (t_dir *)malloc(sizeof(*node))))
		return (NULL);
	if (!(node->name = cpystr(dir->d_name)))
		return (0);
	node->type = dir->d_type;
	if (!(dolong(node, path, dir)))
	{
		ft_strdel(&(node->name));
		free(node);
		return (NULL);
	}
	if (*start)
		node->next = *start;
	else
		node->next = NULL;
	return (node);
}

t_dir	*parsedir(char *path, t_opt *opt)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_dir			*lst;

	lst = NULL;
	if (!(dirp = opendir(path)))
	{
		throwerror(path);
		return (NULL);
	}
	while ((dir = readdir(dirp)) != NULL)
	{
		if (dir->d_name[0] != '.' || opt->all == 1)
		{
			if (!(lst = dolist(&lst, dir, path)))
			{
				closedir(dirp);
				return (NULL);
			}
		}
	}
	closedir(dirp);
	return (lst);
}

t_dir	*parselink(char *path)
{
	t_dir	*node;

	if (!(node = (t_dir *)malloc(sizeof(*node))))
		return (NULL);
	if (!(node->name = cpystr(path)))
	{
		free(node);
		return (NULL);
	}
	if (!(adddata(node, path)))
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

int		dirhandler(char *path, t_opt *opt)
{
	t_dir	*start;

	start = NULL;
	if (checkdir(path, opt))
	{
		if (!(start = parselink(path)))
			return (0);
		displaycontent(&start, opt);
		freelist(&start, opt);
		return (1);
	}
	if (!(start = parsedir(path, opt)))
		return (0);
	sortlist(&start, opt);
	displaycontent(&start, opt);
	recdir(&start, path, opt);
	freelist(&start, opt);
	return (1);
}
