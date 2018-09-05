/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:17:43 by lguiller          #+#    #+#             */
/*   Updated: 2018/09/05 09:45:59 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init_elem_lst(t_all *all)
{
	int			i;
	const char	elem_lst[ELEM_LIST_LEN][ELEM_LEN] = {"cam", "spot", "plane",
		"sphere", "cone", "cylinder"};

	i = -1;
	while (++i < ELEM_LIST_LEN)
		ft_strcpy(all->elem_lst[i], elem_lst[i]);
}

void		ft_init_mlx(t_all *all)
{
	all->ptr.mlx = mlx_init();
	all->ptr.win = mlx_new_window(all->ptr.mlx, WIN_X, WIN_Y, "rtv1");
	all->ptr.img = mlx_new_image(all->ptr.mlx, WIN_X, WIN_Y);
	all->ptr.data = mlx_get_data_addr(all->ptr.img, &all->ptr.bpp, &all->ptr.sl,
		&all->ptr.endian);
}

void		ft_init_values(t_all *all, t_rt *rt)
{
	if (!(all->cam = ft_find_link(&all->scene, "cam")))
		ft_error("error: no object cam", 1, ft_puterror);
	if (!(all->spot = ft_find_link(&all->scene, "spot")))
		ft_error("error: no object spot", 1, ft_puterror);
	all->pos_cam.x = all->cam->px;
	all->pos_cam.y = all->cam->py;
	all->pos_cam.z = all->cam->pz;
	all->pos_spot.x = all->spot->px;
	all->pos_spot.y = all->spot->py;
	all->pos_spot.z = all->spot->pz;
	rt->tp = &all->scene;
	rt->color = 0;
	rt->first = 0;
	rt->d = 0.0;
	all->d = -1.0;
	rt->good = NULL;
}

void		ft_init_vect(t_all *all, t_shadow *shad, t_scene *tp)
{
	t_rot	new;

	new.uni = all->uni_cam;
	new.pos = all->pos_cam;
	shad->p2.x = new.uni.x * all->d + new.pos.x;
	shad->p2.y = new.uni.y * all->d + new.pos.y;
	shad->p2.z = new.uni.z * all->d + new.pos.z;
	new = ft_rotation(tp, &all->uni_cam, &all->pos_cam);
	shad->p.x = new.uni.x * all->d + new.pos.x;
	shad->p.y = new.uni.y * all->d + new.pos.y;
	shad->p.z = new.uni.z * all->d + new.pos.z;
	shad->uni_norme = ft_start_norm_p(shad, *tp);
	shad->spot = ft_find_link(&all->scene, "spot");
	new.pos = all->pos_spot;
	shad->uni_light2.x = new.pos.x - shad->p2.x;
	shad->uni_light2.y = new.pos.y - shad->p2.y;
	shad->uni_light2.z = new.pos.z - shad->p2.z;
	new = ft_rotation(tp, NULL, &all->pos_spot);
	shad->uni_light.x = new.pos.x - shad->p.x;
	shad->uni_light.y = new.pos.y - shad->p.y;
	shad->uni_light.z = new.pos.z - shad->p.z;
	shad->d = sqrt(pow(shad->uni_light.x, 2.0) + pow(shad->uni_light.y, 2.0) +
		pow(shad->uni_light.z, 2.0));
	shad->uni_light = ft_normalize(shad->uni_light);
	shad->uni_light2 = ft_normalize(shad->uni_light2);
}
