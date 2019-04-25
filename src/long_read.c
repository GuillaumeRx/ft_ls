/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:46 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 22:48:26 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		recdir(t_dir **start, char *path, t_opt *opt)
{
	t_dir	*tmp;
	char	*dirpath;

	tmp = *start;
	while (tmp != NULL && opt->rec == 1)
	{
		if ((tmp->type == DT_DIR) && (ft_strcmp(tmp->name, ".") != 0
		&& ft_strcmp(tmp->name, "..") != 0))
		{
			if (!(dirpath = editpath(path, tmp->name)))
				return (0);
			ft_putchar('\n');
			ft_putstr(dirpath);
			ft_putendl(":");
			dirhandler(dirpath, opt);
			ft_strdel(&dirpath);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		dolong(t_dir *node, char *path, struct dirent *dir)
{
	char *filepath;

	if (!(filepath = editpath(path, dir->d_name)))
		return (0);
	if (!(adddata(node, filepath)))
	{
		ft_strdel(&filepath);
		return (0);
	}
	ft_strdel(&filepath);
	return (1);
}

char	*getgroup(gid_t gid)
{
	struct group	*ptr;
	char			*tmp;

	tmp = NULL;
	ptr = getgrgid(gid);
	if (ptr)
		tmp = cpystr(ptr->gr_name);
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
	char			*tmp;

	tmp = NULL;
	ptr = getpwuid(uid);
	if (ptr)
		tmp = cpystr(ptr->pw_name);
	else
		tmp = ft_itoa(uid);
	if (tmp)
		return (tmp);
	else
		return (NULL);
}
