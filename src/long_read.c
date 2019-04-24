/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:18:46 by guroux            #+#    #+#             */
/*   Updated: 2019/04/24 14:50:52 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
