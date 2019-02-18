/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guroux <guroux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:49:12 by guroux            #+#    #+#             */
/*   Updated: 2019/02/18 14:31:25 by guroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	displaycontent(t_dir **start)
{
	t_dir *tmp;

	tmp = *start;
	while (tmp != NULL)
	{
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
