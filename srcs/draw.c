/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:09:38 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/27 10:12:58 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_quit(void)
{
	exit(0);
}

void	ft_draw(t_all all)
{
	int	i;
	int	j;

	ft_init_mlx(&all);
	ft_ray_tracing(&all);
	i = -1;
	while (++i < 50)
	{
		j = -1;
		while (++j < 50)
			mlx_pixel_put(all.ptr.mlx, all.ptr.win, 50 + i, 50 + j, 0xFF0000);
	}
	mlx_hook(all.ptr.win, 17, 0, ft_quit, 0);
	mlx_loop(all.ptr.mlx);
}
