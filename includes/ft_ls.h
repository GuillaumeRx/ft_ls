/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:12:35 by guroux            #+#    #+#             */
/*   Updated: 2019/04/23 15:23:44 by guroux           ###   ########.fr       */
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
#include <errno.h>

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

int					dirhandler(char *path, t_opt *opt);
void				displaycontent(t_dir **start, t_opt *opt);
int					setopt(char *entry, t_opt *opt);
void				sortlist(t_dir **start, t_opt *opt);
void				freelist(t_dir **lst, t_opt *opt);
int					throwerror(char *path);

#endif
