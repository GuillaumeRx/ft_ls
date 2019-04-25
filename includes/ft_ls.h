/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:12:35 by guroux            #+#    #+#             */
/*   Updated: 2019/04/25 22:53:00 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct		s_dir
{
	char			*name;
	char			*rpath;
	unsigned int	type;
	mode_t			mode;
	nlink_t			n_link;
	char			*ownername;
	char			*groupname;
	off_t			size;
	time_t			rawtime;
	quad_t			blocks;
	dev_t			rdev;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_opt
{
	int				rec;
	int				lst;
	int				all;
	int				rev;
	int				tim;
}					t_opt;

/*
** read.c
*/

int					dirhandler(char *path, t_opt *opt);
int					adddata(t_dir *node, char *path);

/*
** long_read.c
*/

char				*getgroup(gid_t gid);
char				*getowner(uid_t uid);
int					dolong(t_dir *node, char *path, struct dirent *dir);
int					recdir(t_dir **start, char *path, t_opt *opt);

/*
** misc.c
*/

int					alpha(t_dir *node1, t_dir *node2);
int					lastmod(t_dir *node1, t_dir *node2);
char				*cpystr(char *src);
int					checkdir(char *path, t_opt *opt);
char				*editpath(char *actual, char *next);

/*
** display.c
*/

void				displaycontent(t_dir **start, t_opt *opt);
void				printgroup(t_dir **start, char *group);
void				printowner(t_dir **start, char *owner);
void				printdate(time_t rawtime);
void				parsemode(mode_t mode);

/*
** display_long.c
*/

void				displaylong(t_dir **start);
void				printminmaj(int size, int minor, int major);

/*
** display_long_2.c
*/

void				calcblocks(t_dir **start);
void				printsize(t_dir *act, int size);
int					calcpadding(t_dir **start);
void				printlink(t_dir **start, nlink_t n_link);

/*
** sort.c
*/

void				sortlist(t_dir **start, t_opt *opt);

/*
** options.c
*/

int					parseopt(char *str, t_opt *opt);

/*
** list.c
*/

void				freelist(t_dir **lst, t_opt *opt);

/*
** error.c
*/

int					throwerror(char *path);
void				usage(char opt);

#endif
