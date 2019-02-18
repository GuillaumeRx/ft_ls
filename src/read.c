/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:09:33 by guroux            #+#    #+#             */
/*   Updated: 2019/02/18 19:49:08 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		addnode(t_dir **head, struct dirent *dir, char *path)
{
	t_dir 			*last;
	t_dir 			*node;
	struct stat		buf;
	struct passwd	*pwd;
	struct group	*grp;
	char			*filepath;

	filepath = ft_strjoin(path, "/");
	filepath = ft_strjoin(filepath, dir->d_name);
	if (!(node = (t_dir *)malloc(sizeof(t_dir))))
		return (0);
	if ((lstat(filepath, &buf)) < 0)
		return (0);
	last = (*head);
	if (!(pwd = getpwuid(buf.st_uid)))
		return (0);
	node->name = dir->d_name;
	node->type = dir->d_type;
	node->rawtime = buf.st_mtime;
	node->ownername = pwd->pw_name;
	if (!(grp = getgrgid(pwd->pw_gid)))
		return (0);
	node->groupname = grp->gr_name;
	node->mode = buf.st_mode;
	node->n_link = buf.st_nlink;
	node->size = buf.st_size;
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

	start = NULL;
	if (!(dirp = opendir(path)))
		return (0);
	while ((dir = readdir(dirp)) != NULL)
	{
		if (dir->d_name[0] != '.' || opt->all)
			if (!(addnode(&start, dir, path)))
				return (0);
	}
	sortlist(&start, opt);
	displaycontent(&start);
	tmp = start;
	while (tmp != NULL && opt->rec)
	{
		if ((tmp->type == DT_DIR) && (ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0))
		{
			if (ft_strcmp(tmp->name, ".") != 0)
			{
				fullpath = ft_strjoin(path, "/");
				fullpath = ft_strjoin(fullpath, tmp->name);
			}
			else
				fullpath = tmp->name;
			ft_putstr(fullpath);
			ft_putendl(" :");
			if (!(parsedir(fullpath, opt)))
				return (0);
		}
		tmp = tmp->next;
	}
	freelist(&start);
	return (1);
}
