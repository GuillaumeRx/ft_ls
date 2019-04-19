/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/04/19 20:38:09 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		checkdir(char *path)
{
	struct stat		buf;

	if ((lstat(path, &buf)) < 0)
		return (0);
	if (S_ISLNK(buf.st_mode))
		return (1);
	return (0);
}

char	*getgroup(gid_t gid)
{
	struct group	*ptr;
	char			*tmp = NULL;

	ptr = getgrgid(gid);
	if (ptr)
		tmp = ft_strdup(ptr->gr_name);
	else
		tmp = ft_itoa(gid);
	if (tmp)
		return (tmp);
	else
		return (NULL);
}

char	*getowner(uid_t uid)
{
	struct passwd	*ptr;
	char			*tmp = NULL;

	ptr = getpwuid(uid);
	if (ptr)
		tmp = ft_strdup(ptr->pw_name);
	else
		tmp = ft_itoa(uid);
	if (tmp)
		return (tmp);
	else
		return (NULL);
}

char	*editpath(char *actual, char *next)
{
	char *tmp;
	char *buf;

	if (actual[ft_strlen(actual) - 1] != '/')
	{
		if (!(tmp = ft_strjoin(actual, "/")))
			return (NULL);
		if (!(buf = ft_strjoin(tmp, next)))
			return (NULL);
		ft_strdel(&tmp);
	}
	else
	{
		if (!(buf = ft_strjoin(actual, next)))
			return (NULL);
	}
	return (buf);
}

int		getdir(t_dir **head, char *path)
{

	struct stat		buf;
	t_dir			*node;

	if (!(node = (t_dir *)malloc(sizeof(t_dir))))
		return (0);
	if ((lstat(path, &buf)) < 0)
		return(throwerror(path));
	node->name = ft_strdup(path);
	node->rawtime = buf.st_mtime;
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
	node->blocks = buf.st_blocks;
	if (!(node->ownername = getowner(buf.st_uid)))
		return (0);
	if (!(node->groupname = getgroup(buf.st_gid)))
		return (0);
	if (S_ISLNK(buf.st_mode))
	{
		node->rpath = (char *)malloc(sizeof(char) * 100);
		node->rpath[readlink(path, node->rpath, 99)] = '\0';
	}
	(*head) = node;
	(*head)->next = NULL;
	return (1);
}

int		adddata(t_dir *node, struct dirent *dir, char *path, t_opt *opt)
{
	struct stat		buf;
	char			*filepath;

	ft_putendl("plip");
	if (!(filepath = editpath(path, dir->d_name)))
		return (-1);
	if ((lstat(filepath, &buf)) < 0)
	{
		ft_strdel(&filepath);
		return(throwerror(path));
	}
	node->name = ft_strdup(dir->d_name);
	node->type = dir->d_type;
	node->rawtime = buf.st_mtime;
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
	node->blocks = buf.st_blocks;
	if (opt->lst)
	{
		if (!(node->ownername = getowner(buf.st_uid)))
			return (-1);
		if (!(node->groupname = getgroup(buf.st_gid)))
			return (-1);
	}
	else
	{
		node->ownername = NULL;
		node->groupname = NULL;
	}
	ft_putendl("plop");
	if (S_ISLNK(buf.st_mode))
	{
		node->rpath = (char *)malloc(sizeof(char) * 40);
		node->rpath[readlink(filepath, node->rpath, 39)] = '\0';
	}
	// ft_strdel(&filepath);
	return (1);
}

t_dir	*dolist(t_dir **start, struct dirent *dir, char *path, t_opt *opt)
{
	t_dir	*node;

	if (!(node = (t_dir *)malloc(sizeof(*node))))
		return (NULL);
	if (!(adddata(node, dir, path, opt)))
	{
		free(node);
		return (NULL);
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

int		parsedir(char *path, t_opt *opt)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_dir			*start = NULL;
	t_dir			*tmp;
	char			*fullpath;

	if (checkdir(path) && opt->lst == 1)
	{
		if (!(getdir(&start, path)))
			return (0);
		displaycontent(&start, opt);
	}
	else
	{
		if (!(dirp = opendir(path)))
			return(throwerror(path));
		while ((dir = readdir(dirp)) != NULL)
		{
			if (dir->d_name[0] != '.' || opt->all == 1)
			{
				if (!(start = dolist(&start, dir, path, opt)))
				{
					closedir(dirp);
					return (0);
				}
			}
		}
		closedir(dirp);
		sortlist(&start, opt);
		displaycontent(&start, opt);
		tmp = start;
		while (tmp != NULL && opt->rec == 1)
		{
			if ((tmp->type == DT_DIR) && (ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0))
			{
				if (!(fullpath = editpath(path, tmp->name)))
					return (0);
				ft_putchar('\n');
				ft_putstr(fullpath);
				ft_putendl(" :");
				parsedir(fullpath, opt);
				ft_strdel(&fullpath);
			}
			tmp = tmp->next;
		}
	}
	freelist(&start);
	return (1);
}
