/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:09:38 by bede-fre          #+#    #+#             */
/*   Updated: 2018/08/09 16:23:41 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_fill_pixel(t_mlx *mlx, int x, int y, int col)
{
	if ((y >= 0 && y < WIN_Y) && (x >= 0 && x < WIN_X))
		if (mlx->endian == 0 && mlx->bpp == 32)
		{
			((char *)(mlx->data))[((x * 4) + (y * mlx->sl))] =
				(char)col;
			((char *)(mlx->data))[((x * 4) + (y * mlx->sl)) + 1] =
				(char)(col >> 8);
			((char *)(mlx->data))[((x * 4) + (y * mlx->sl)) + 2] =
				(char)(col >> 16);
			((char *)(mlx->data))[((x * 4) + (y * mlx->sl)) + 3] =
				(char)(col >> 24);
		}
}

static int	ft_quit(void)
{
	exit(0);
}

void		ft_draw(t_all all)
{
	int	i;
	int	j;

	ft_init_mlx(&all);
	i = -1;
	while (++i < WIN_X)
	{
		j = -1;
		while (++j < WIN_Y)
			ft_ray_tracing(&all, i, j);
	}
	mlx_hook(all.ptr.win, 17, 0L, ft_quit, 0);
	mlx_hook(all.ptr.win, 2, (1L << 0), ft_key_press, 0);
	mlx_hook(all.ptr.win, 4, (1L << 2), ft_button_press, &all);
	mlx_put_image_to_window(all.ptr.mlx, all.ptr.win, all.ptr.img, 0, 0);
	mlx_loop(all.ptr.mlx);
}
