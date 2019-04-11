/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:38:32 by guroux            #+#    #+#             */
/*   Updated: 2019/04/11 21:45:36 by guroux           ###   ########.fr       */
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
