/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:16:28 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 22:52:46 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		alpha(t_dir *node1, t_dir *node2)
{
	return (ft_strcmp(node1->name, node2->name) > 0 ? 1 : 0);
}

int		lastmod(t_dir *node1, t_dir *node2)
{
	if (node1->rawtime < node2->rawtime)
		return (1);
	else if (node1->rawtime == node2->rawtime)
		if (ft_strcmp(node1->name, node2->name) > 0)
			return (1);
	return (0);
}

char	*cpystr(char *src)
{
	char *dst;

	if (!(dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	dst = ft_strcpy(dst, src);
	return (dst);
}

int		checkdir(char *path, t_opt *opt)
{
	struct stat		buf;

	if ((lstat(path, &buf)) < 0)
		return (0);
	if (S_ISLNK(buf.st_mode) && opt->lst == 1)
		return (1);
	else if (S_ISREG(buf.st_mode))
		return (1);
	return (0);
}

char	*editpath(char *actual, char *next)
{
	char *tmp;
	char *buf;

	if (!(tmp = ft_strjoin(actual, "/")))
		return (NULL);
	if (!(buf = ft_strjoin(tmp, next)))
		return (NULL);
	ft_strdel(&tmp);
	return (buf);
}
