/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/17 16:09:50 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene		*ft_find_link(t_scene *scene, char name[], int i)
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

static void	ft_init_values(t_all *all)
{
	t_scene		*cam;
	t_scene		*spot;

	if (!(cam = ft_find_link(&all->scene, "cam", 1)))
		ft_error("error: no object cam", 1, ft_puterror);
	all->campos.x = (double)cam->px;
	all->campos.y = (double)cam->py;
	all->campos.z = (double)cam->pz;
	if (!(spot = ft_find_link(&all->scene, "spot", 1)))
		ft_error("error: no object spot", 1, ft_puterror);
	all->spotpos.x = (double)spot->px;
	all->spotpos.y = (double)spot->py;
	all->spotpos.z = (double)spot->pz;
}

static void	ft_find_coord_pixel(t_all *all, int x, int y)
{
	all->pointpos.x = all->campos.x - 1.0 * (PLAN_W / 2.0);
	all->pointpos.y = all->campos.y + 1.0 * (PLAN_H / 2.0);
	all->pointpos.z = all->campos.z + 1.0 * PLAN_D;
	all->pointpos.x = all->pointpos.x + (double)x * INCR_X;
	all->pointpos.y = all->pointpos.y - (double)y * INCR_Y;
	all->lg = sqrt(pow(all->pointpos.x, 2.0) + pow(all->pointpos.y, 2.0) + pow(all->pointpos.z, 2.0));
	all->univect.x = all->pointpos.x / all->lg;
	all->univect.y = all->pointpos.y / all->lg;
	all->univect.z = all->pointpos.z / all->lg;
}

static int	ft_shadow(t_all *all, t_scene *tp, double d)
{
	t_coord_3d	p;
	t_coord_3d	vect_norme;
	t_coord_3d	vect_light;
	t_scene		*spot;
	double		angle;

	p.x = all->univect.x * d;
	p.y = all->univect.y * d;
	p.z = all->univect.z * d;
	vect_norme.x = p.x - tp->px;
	vect_norme.y = p.y - tp->py;
	vect_norme.z = p.z - tp->pz;
	vect_light.x = all->spotpos.x - p.x;
	vect_light.y = all->spotpos.y - p.y;
	vect_light.z = all->spotpos.z - p.z;
	angle = (vect_norme.x * vect_light.x + vect_norme.y * vect_light.y + vect_norme.z * vect_light.z) / sqrt((pow(vect_norme.x, 2.0) + pow(vect_norme.y, 2.0) + pow(vect_norme.z, 2.0)) * (pow(vect_light.x, 2.0) + pow(vect_light.y, 2.0) + pow(vect_light.z, 2.0)));
	angle = (angle < 0) ? 0 : angle;
	spot = ft_find_link(&all->scene, "spot", 1);
	angle = angle * (spot->p1 / 100.0);
	return (ft_rgba(tp->p1 * angle, tp->p2 * angle, tp->p3 * angle, 0));
}

void		ft_ray_tracing(t_all *all, int x, int y)
{
	t_scene	*tp;
	t_scene	*good;
	double	d;
	int		color;
	int		first;

	ft_init_values(all);
	ft_find_coord_pixel(all, x, y);
//	printf("[%.4f %.4f %.4f %.4f]\n", all->pointpos.x, all->pointpos.y, all->pointpos.z, all->lg);
//	printf("[%.4f %.4f %.4f]\n", all->pointpos.x/all->lg, all->pointpos.y/all->lg, all->pointpos.z/ all->lg);
	tp = &all->scene;
	color = 0;
	first = 0;
	d = 0.0;
	all->d = -1.0;
	good = NULL;
	while (tp)
	{
		if (ft_strequ(tp->name, "sphere"))
			d = ft_sphere(all, tp);
		else if (ft_strequ(tp->name, "plane"))
			d = ft_plane(all, tp);
		else if (ft_strequ(tp->name, "cone"))
			d = ft_cone(all, tp);
		else if (ft_strequ(tp->name, "cylinder"))
			d = ft_cylinder(all, tp);
		if (d >= 0.0)
		{
			if (d < all->d || ++first == 1)
			{
				all->d = d;
				good = tp;
				color = ft_rgba(tp->p1, tp->p2, tp->p3, 0);
			}
		}
		tp = tp->next;
	}
	if (all->test == 1)
		printf("[%.4f]\n", all->d);
//	if (all->d >= 0.0)
	if (good)
		mlx_pixel_put(all->ptr.mlx, all->ptr.win, x, y, ft_shadow(all, good, all->d));
}
