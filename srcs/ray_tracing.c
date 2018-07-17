/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/17 12:22:31 by lguiller         ###   ########.fr       */
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

	cam = ft_find_link(&all->scene, "cam", 1);
	all->campos.x = (double)cam->px;
	all->campos.y = (double)cam->py;
	all->campos.z = (double)cam->pz;
}

static void	ft_find_coord_pixel(t_all *all, int x, int y)
{
	all->pointpos.x = all->campos.x - 1.0 * (PLAN_W / 2.0);
	all->pointpos.y = all->campos.y + 1.0 * (PLAN_H / 2.0);
	all->pointpos.z = all->campos.z + 1.0 * PLAN_D;
	all->pointpos.x = all->pointpos.x + (double)x * INCR_X;
	all->pointpos.y = all->pointpos.y - (double)y * INCR_Y;
	all->lg = sqrt(pow(all->pointpos.x, 2.0) + pow(all->pointpos.y, 2.0) + pow(all->pointpos.z, 2.0));
}

void		ft_ray_tracing(t_all *all, int x, int y)
{
	t_scene	*tp;
	double	d;
	int		color;

	ft_init_values(all);
	ft_find_coord_pixel(all, x, y);
//	printf("[%.4f %.4f %.4f %.4f]\n", all->pointpos.x, all->pointpos.y, all->pointpos.z, all->lg);
//	printf("[%.4f %.4f %.4f]\n", all->pointpos.x/all->lg, all->pointpos.y/all->lg, all->pointpos.z/ all->lg);
	tp = &all->scene;
	color = 0;
	d = 0.0;
	all->d = -1.0;
	while (tp)
	{
		if (ft_strequ(tp->name, "sphere"))
			d = ft_sphere(all, tp);
		else if (ft_strequ(tp->name, "plane"))
			d = ft_plane(all);
		else if (ft_strequ(tp->name, "cone"))
			d = ft_cone(all, tp);
		else if (ft_strequ(tp->name, "cylinder"))
			d = ft_cylinder(all, tp);
		if (d >= 0.0)
		{
			if (all->d < 0.0 && (all->d = d))
				color = ft_rgba(tp->p1, tp->p2, tp->p3, 0);
			if (d < all->d && (all->d = d))
				color = ft_rgba(tp->p1, tp->p2, tp->p3, 0);
		}
		tp = tp->next;
	}
	//	printf("[%.4f]\n", all->d);
	if (all->d >= 0.0)
		mlx_pixel_put(all->ptr.mlx, all->ptr.win, x, y, color);
}
