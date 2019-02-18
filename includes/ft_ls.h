/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:12:35 by guroux            #+#    #+#             */
/*   Updated: 2019/02/18 19:45:34 by guroux           ###   ########.fr       */
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

typedef struct		s_dir
{
	char			*name;
	unsigned int	type;
	mode_t			mode;
	nlink_t			n_link;
	char			*ownername;
	char			*groupname;
	off_t			size;
	time_t			rawtime;
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

int					parsedir(char *path, t_opt *opt);
void				displaycontent(t_dir **start);
int					setopt(char *entry, t_opt *opt);
void				sortlist(t_dir **start, t_opt *opt);
void				freelist(t_dir **node);

#endif
