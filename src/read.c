/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/03/12 17:42:02 by guroux           ###   ########.fr       */
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
	{
		perror(ft_strjoin("ft_ls: ", path));
		return (0);
	}
	if (!(pwd = getpwuid(buf.st_uid)))
		return (0);
	node->name = path;
	node->rawtime = buf.st_mtime;
	node->ownername = pwd->pw_name;
	if (!(grp = getgrgid(pwd->pw_gid)))
		return (0);
	node->groupname = grp->gr_name;
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

int		addnode(t_dir **head, struct dirent *dir, char *path)
{
	t_dir 			*last;
	t_dir 			*node;
	struct stat		buf;
	struct passwd	*pwd;
	struct group	*grp;
	char			*filepath;

	filepath = editpath(path, dir->d_name);
	if (!(node = (t_dir *)malloc(sizeof(t_dir))))
		return (0);
	if ((lstat(filepath, &buf)) < 0)
	{
		perror(ft_strjoin("ft_ls: ", path));
		return (0);
	}
	last = (*head);
	if (!(pwd = getpwuid(buf.st_uid)))
		node->ownername = ft_itoa(buf.st_uid);
	else
		node->ownername = pwd->pw_name;
	node->name = dir->d_name;
	node->type = dir->d_type;
	node->rawtime = buf.st_mtime;
	if (!(grp = getgrgid(buf.st_gid)))
		return (0);
	node->groupname = grp->gr_name;
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
	if ((*head) == NULL)
		(*head) = node;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
	return (1);
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
	fullpath = ft_strdup("");
	if (checkdir(path) && opt->lst == 1)
	{
		getdir(&start, path);
		displaycontent(&start, opt);
	}
	else
	{
		if (!(dirp = opendir(path)))
		{
			perror(ft_strjoin("ft_ls: ", path));
			return (0);
		}
		while ((dir = readdir(dirp)) != NULL)
		{
			if (dir->d_name[0] != '.' || opt->all)
				if (!(addnode(&start, dir, path)))
				{
					closedir(dirp);
					return (0);
				}
		}
		sortlist(&start, opt);
		displaycontent(&start, opt);
		tmp = start;
		while (tmp != NULL && opt->rec == 1)
		{
			if ((tmp->type == DT_DIR) && (ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0))
			{
				if (ft_strcmp(tmp->name, ".") != 0)
				{
					if (!(fullpath = editpath(path, tmp->name)))
						return (0);
				}
				else
					fullpath = tmp->name;
				ft_putchar('\n');
				ft_putstr(fullpath);
				ft_putendl(" :");
				parsedir(fullpath, opt);
			}
			tmp = tmp->next;
		}
		closedir(dirp);
	}
	
	freelist(&start);
	return (1);
}
