/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/26 16:43:35 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*ft_find_link(t_scene *scene, char name[], int i)
{
	t_scene	*tp;

	tp = scene;
	while (tp)
	{
		if (ft_strequ(tp->name, name) && --i == 0)
			return (tp);
		tp = tp->next;
	}
	return (NULL);
}

static void		ft_init_values(t_all *all, t_rt *rt)
{
	if (!(all->cam = ft_find_link(&all->scene, "cam", 1)))
		ft_error("error: no object cam", 1, ft_puterror);
	if (!(all->spot = ft_find_link(&all->scene, "spot", 1)))
		ft_error("error: no object spot", 1, ft_puterror);
	all->campos.x = all->cam->px;
	all->campos.y = all->cam->py;
	all->campos.z = all->cam->pz;
	rt->tp = &all->scene;
	rt->color = 0;
	rt->first = 0;
	rt->d = 0.0;
	all->d = -1.0;
	rt->good = NULL;
}

static void		ft_find_coord_pixel(t_all *all, int x, int y)
{
	t_mat3	pointpos;

	pointpos.x = all->cam->px - PLAN_W / 2.0;
	pointpos.y = all->cam->py + PLAN_H / 2.0;
	pointpos.z = all->cam->pz + PLAN_D;
	pointpos.x += ((double)x * INCR_X);
	pointpos.y -= ((double)y * INCR_Y);
	all->lg = sqrt(pow(pointpos.x, 2.0) + pow(pointpos.y, 2.0)
		+ pow(pointpos.z, 2.0));
	pointpos.x -= all->cam->px;
	pointpos.y -= all->cam->py;
	pointpos.z -= all->cam->pz;
	all->univect.x = pointpos.x / all->lg;
	all->univect.y = pointpos.y / all->lg;
	all->univect.z = pointpos.z / all->lg;
	ft_rot_x(&all->univect, ft_rad(all->cam->dx));
	ft_rot_y(&all->univect, ft_rad(all->cam->dy));
	ft_rot_z(&all->univect, ft_rad(all->cam->dz));
}

t_funct			ft_get_funct(char *name)
{
	const char		*shape_name[] = {"sphere", "plane", "cone", "cylinder"};
	const t_funct	function_name[] = {&ft_sphere, &ft_plane, &ft_cone,
		&ft_cylinder};
	int				i;

	i = -1;
	while (++i < ELEM_LIST_LEN - 2)
	{
		if (ft_strequ(name, shape_name[i]) == 1)
			return (function_name[i]);
	}
	return (NULL);
}

void			ft_ray_tracing(t_all *all, int x, int y)
{
	t_rt	rt;

	ft_init_values(all, &rt);
	ft_find_coord_pixel(all, x, y);
	while (rt.tp)
	{
		if ((rt.f = ft_get_funct(rt.tp->name)))
			rt.d = rt.f(all, rt.tp, &all->univect, &all->campos);
		if (rt.d >= 0.0)
			if (rt.d < all->d || ++rt.first == 1)
			{
				all->d = rt.d;
				rt.good = rt.tp;
				rt.color = ft_rgba(rt.tp->p1, rt.tp->p2, rt.tp->p3, 0);
			}
		rt.tp = rt.tp->next;
	}
	if (all->test == 1)
		printf("distance: %.4f\n", all->d);
	if (rt.good && (ft_strequ(rt.good->name, "sphere") == 1 || ft_strequ(rt.good->name, "plane") == 1))
		ft_fill_pixel(&all->ptr, x, y, ft_shadow_object(all, rt.good, all->d));
	else if (rt.good)
		ft_fill_pixel(&all->ptr, x, y, rt.color);
}
