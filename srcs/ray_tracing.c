/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/05 16:28:39 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*ft_find_link(t_scene *scene, char name[])
{
	t_scene	*tp;

	tp = scene;
	while (tp)
	{
		if (ft_strequ(tp->name, name))
			return (tp);
		tp = tp->next;
	}
	return (NULL);
}

static void		ft_find_coord_pixel(t_all *all, int x, int y)
{
	t_mat3	pointpos;

	pointpos.x = all->cam->px - PLAN_W / 2.0;
	pointpos.y = all->cam->py + PLAN_H / 2.0;
	pointpos.z = all->cam->pz + PLAN_D;
	pointpos.x += ((double)x * INCR_X);
	pointpos.y -= ((double)y * INCR_Y);
	pointpos.x -= all->cam->px;
	pointpos.y -= all->cam->py;
	pointpos.z -= all->cam->pz;
	all->uni_cam = ft_normalize(pointpos);
	all->uni_cam = ft_rot_x(all->uni_cam, ft_rad(all->cam->dx));
	all->uni_cam = ft_rot_y(all->uni_cam, ft_rad(all->cam->dy));
	all->uni_cam = ft_rot_z(all->uni_cam, ft_rad(all->cam->dz));
}

t_funct			ft_get_funct(char *name)
{
	const char		*shape_name[] = {"sphere", "plane", "cone", "cylinder"};
	const t_funct	function_name[] = {&ft_sphere, &ft_plane, &ft_cone,
		&ft_cylinder};
	int				i;

	i = -1;
	while (++i < ELEM_LIST_LEN - 2)
		if (ft_strequ(name, shape_name[i]))
			return (function_name[i]);
	return (NULL);
}

void			ft_ray_tracing(t_all *all, int x, int y)
{
	t_rt	rt;
	t_funct	f;
	double	d;

	ft_init_values(all, &rt);
	ft_find_coord_pixel(all, x, y);
	while (rt.tp)
	{
		d = -1.0;
		if ((f = ft_get_funct(rt.tp->name)))
			d = f(rt.tp, &all->uni_cam, &all->pos_cam);
		if (d >= 0.0 && (d < all->d || ++rt.first == 1))
		{
			all->d = d;
			rt.good = rt.tp;
			rt.color = ft_rgba((unsigned char)rt.tp->p1,
				(unsigned char)rt.tp->p2, (unsigned char)rt.tp->p3, 0);
		}
		rt.tp = rt.tp->next;
	}
	if (rt.good)
		ft_fill_pixel(&all->ptr, x, y, ft_shadow_object(all, rt.good));
}
