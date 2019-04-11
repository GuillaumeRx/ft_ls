/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/04/11 23:16:27 by guroux           ###   ########.fr       */
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
		free(tmp);
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
	struct passwd	*pwd;
	struct group	*grp;
	t_dir			*node;
	if (!(node = (t_dir *)malloc(sizeof(t_dir))))
		return (0);
	if ((lstat(path, &buf)) < 0)
		return(throwerror(path));
	if (!(pwd = getpwuid(buf.st_uid)))
		node->ownername = ft_itoa(buf.st_uid);
	else
		node->ownername = ft_strdup(pwd->pw_name);
	node->name = ft_strdup(path);
	node->rawtime = buf.st_mtime;
	if (!(grp = getgrgid(buf.st_gid)))
		node->groupname = ft_itoa(buf.st_gid);
	else
		node->groupname = ft_strdup(grp->gr_name);
	node->groupname = ft_strdup(grp->gr_name);
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
	node->blocks = buf.st_blocks;
	if (S_ISLNK(buf.st_mode))
	{
		node->rpath = (char *)malloc(sizeof(char) * 100);
		node->rpath[readlink(path, node->rpath, 99)] = '\0';
	}
	node->next = NULL;
	(*head) = node;
	return (1);
}

int		adddata(t_dir *node, struct dirent *dir, char *path)
{
	struct stat		buf;
	struct passwd	*pwd;
	struct group	*grp;
	char			*filepath;

	if (!(filepath = editpath(path, dir->d_name)))
		return (0);
	if ((lstat(filepath, &buf)) < 0)
	{
		free(filepath);
		return(throwerror(path));
	}
	if (!(pwd = getpwuid(buf.st_uid)))
		node->ownername = ft_itoa(buf.st_uid);
	else
		node->ownername = ft_strdup(pwd->pw_name);
	node->name = ft_strdup(dir->d_name);
	node->type = dir->d_type;
	node->rawtime = buf.st_mtime;
	if (!(grp = getgrgid(buf.st_gid)))
		node->groupname = ft_itoa(buf.st_gid);
	else
		node->groupname = ft_strdup(grp->gr_name);
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
	node->blocks = buf.st_blocks;
	if (S_ISLNK(buf.st_mode))
	{
		node->rpath = (char *)malloc(sizeof(char) * 100);
		node->rpath[readlink(filepath, node->rpath, 99)] = '\0';
	}
	node->next = NULL;
	free(filepath);
	return (1);
}

t_dir	*dolist(t_dir **start, struct dirent *dir, char *path)
{
	t_dir	*node;

	if (!(node = (t_dir *)malloc(sizeof(*node))))
		return (NULL);
	if (!(adddata(node, dir, path)))
	{
		free(node);
		return (NULL);
	}
	if (*start)
	{
		node->next = *start;
		return (node);
	}
	return (node);
}

int		parsedir(char *path, t_opt *opt)
{
	DIR				*dirp;
	struct dirent	*dir;
	t_dir			*start;
	t_dir			*tmp;
	char			*fullpath;

	dir = NULL;
	start = NULL;
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
				if (!(start = dolist(&start, dir, path)))
				{
					closedir(dirp);
					freelist(&start);
					return (0);
				}
			}
		}
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
				free(fullpath);
			}
			tmp = tmp->next;
		}
		closedir(dirp);
	}
	freelist(&start);
	return (1);
}
