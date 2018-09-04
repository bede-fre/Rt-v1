/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:05:31 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/04 17:58:10 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** system("leaks rtv1 | grep 'leaked bytes' | cut -c16- | cut -c-7");
*/

int		ft_button_press(int button, int x, int y, t_all *all)
{
	if (button == L_CLIC)
	{
		all->test = 1;
		ft_ray_tracing(all, x, y);
		all->test = 0;
	}
	return (0);
}

int		ft_key_press(int key, void *p)
{
	(void)p;
	if (key == ESC)
		exit(0);
	return (0);
}
