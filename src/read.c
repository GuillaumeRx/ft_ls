/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:08:08 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 17:05:02 by guroux           ###   ########.fr       */
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

t_dir	*dolist(t_dir **start, struct dirent *dir, char *path, t_opt *opt)
{
	t_dir	*node;
	char	*filepath;

	if (!(node = (t_dir *)malloc(sizeof(*node))))
		return (NULL);
	if (!(node->name = cpystr(dir->d_name)))
		return (0);
	node->type = dir->d_type;
	if (opt->lst == 1)
	{
		if (!(filepath = editpath(path, dir->d_name)))
		{
			ft_strdel(&node->name);
			free(node);
			return (NULL);
		}
		if (!(adddata(node, filepath)))
		{
			ft_strdel(&node->name);
			free(node);
			return (NULL);
		}
		ft_strdel(&filepath);
	}
	if (*start)
	{
		node->next = *start;
		return (node);
	}
	else
	{
		node->next = NULL;
		return (node);
	}
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
			if (!(lst = dolist(&lst, dir, path, opt)))
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
	t_dir	*tmp;
	char	*dirpath;

	start = NULL;
	if (checkdir(path) && opt->lst == 1)
	{
		ft_putendl("plop");
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
	tmp = start;
	while (tmp != NULL && opt->rec == 1)
	{
		if ((tmp->type == DT_DIR) && (ft_strcmp(tmp->name, ".") != 0
		&& ft_strcmp(tmp->name, "..") != 0))
		{
			if (!(dirpath = editpath(path, tmp->name)))
				return (0);
			ft_putchar('\n');
			ft_putstr(dirpath);
			ft_putendl(" :");
			dirhandler(dirpath, opt);
			ft_strdel(&dirpath);
		}
		tmp = tmp->next;
	}
	freelist(&start, opt);
	return (1);
}
