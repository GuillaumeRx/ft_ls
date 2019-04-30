/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:38:32 by guroux            #+#    #+#             */
/*   Updated: 2019/04/30 11:50:45 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		throwerror(char *path)
{
	char *str;

	if (!(str = ft_strjoin("ft_ls: ", path)))
		return (0);
	perror(str);
	free(str);
	return (0);
}

void	usage(char opt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: ft_ls [-Ralrt] [file ...]", 2);
}
