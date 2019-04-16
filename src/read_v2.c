/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:00:43 by guroux            #+#    #+#             */
/*   Updated: 2019/04/16 18:28:40 by guroux           ###   ########.fr       */
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

int		makelst(char *path, t_opt *opt)
{
	t_dir			*start = NULL;
	t_dir			*node = NULL;
	DIR				*dirp;
	struct dirent	*dir;

	if (checkdir(path) && opt->lst == 1)
	{
		node = (t_dir *)malloc(sizeof(node));
		adddata(node, path, opt);
		node->next = NULL;
		start = node;
	}
	else
	{
		while ((dir = readdir(dirp)) != NULL)
		{
			if (dir->d_name[0] != '.' || opt->all == 1)
			{
				node = (t_dir *)malloc(sizeof(node));
				adddata(node, path, opt);
				if (start)
				{
					node->next = start;
					start = node;
				}
				else
				{
					node->next = NULL;
					start = node;
				}
			}
		}
	}
	return (start);
}

int		makelst(char *path, t_opt *opt)
{
	t_dir	*head = NULL;

	head = datafiller(path, opt);
}
