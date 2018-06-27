/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:05:31 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/27 11:01:26 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_button_press(int button, int x, int y, t_all *all)
{
	if (button == 1)
		ft_ray_tracing(all, x, y);
	return (0);
}

int		ft_key_press(int key, void *p)
{
	(void)p;
	if (key == 53)
		exit(0);
	return (0);
}

void	ft_init_mlx(t_all *all)
{
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WIN_X, WIN_Y, "rtv1");
}
