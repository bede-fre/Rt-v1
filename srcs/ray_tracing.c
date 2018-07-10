/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/10 17:39:16 by bede-fre         ###   ########.fr       */
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

static double	ft_sphere (t_all *all, t_scene *tp)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;

	a = pow(all->pointpos.x / all->lg, 2.0) + pow(all->pointpos.y / all->lg, 2.0)
		+ pow(all->pointpos.z / all->lg, 2.0);
	b = 2.0 * ((all->pointpos.x / all->lg) * (all->campos.x - (double)tp->px)
		+ (all->pointpos.y / all->lg) * (all->campos.y - (double)tp->py)
		+ (all->pointpos.z / all->lg) * (all->campos.z - (double)tp->pz));
	c = (pow(all->campos.x - (double)tp->px, 2.0)
		+ (pow(all->campos.y - (double)tp->py, 2.0) + pow(all->campos.z
		- (double)all->scene.pz, 2.0)) - pow((double)tp->p4, 2.0));
	d = pow(b, 2.0) - 4.0 * a * c;
//	printf("[%.4f %.4f %.4f %.4f]\n", a, b, c, d);
	t1 = 0;
	t2 = 0;
	if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		if (t1 > t2)
			return (t1);
		else
			return (t2);
	}
	else if (d == 0)
		return (t1 = -b / (2.0 * a));
	else
		return (-1.0);
}

static double	ft_plan (t_all *all)
{
	double	d;
	double	t;

	t = -1.0;
	d = -(all->scene.px * all->scene.dx + all->scene.py * all->scene.dy + all->scene.pz * all->scene.dz);
	t = -(((all->scene.px * (all->campos.x - all->pointpos.x))
		+ (all->scene.py * (all->campos.y - all->pointpos.y))
		+ (all->scene.pz * (all->campos.z - all->pointpos.z)) + d)
		/ ((all->scene.px * (all->pointpos.x / all->lg))
		+ (all->scene.py * (all->pointpos.y / all->lg))
		+ (all->scene.pz * (all->pointpos.z / all->lg))));
	printf("[%.4f]\n", t);
	if (t > 0.0001)
		return (t);
	else
		return (-1.0);
}

static double	ft_cone (t_all *all, t_scene *tp)
{
	(void)all;
	(void)tp;
	return (-1.0);
}

static double	ft_barrel (t_all *all, t_scene *tp)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;

	a = pow(all->pointpos.x / all->lg, 2.0) + pow(all->pointpos.y / all->lg, 2.0);
	b = 2.0 * ((all->pointpos.x / all->lg) * (all->campos.x - (double)tp->px)
		+ (all->pointpos.y / all->lg) * (all->campos.y - (double)tp->py));
	c = (pow(all->campos.x - (double)tp->px, 2.0)
		+ (pow(all->campos.y - (double)tp->py, 2.0)) - pow((double)tp->p4, 2.0));
	d = pow(b, 2.0) - 4.0 * a * c;
//	printf("[%.4f %.4f %.4f %.4f]\n", a, b, c, d);
	t1 = 0;
	t2 = 0;
	if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		if (t1 > t2)
			return (t1);
		else
			return (t2);
	}
	else if (d == 0)
		return (t1 = -b / (2.0 * a));
	else
		return (-1.0);
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
	d = 0.0;
	color = 0;
	all->d = -1.0;
	while (tp)
	{
		if (ft_strequ(tp->name, "sphere"))
			d = ft_sphere(all, tp);
		else if (ft_strequ(tp->name, "plan"))
			d = ft_plan(all);
		else if (ft_strequ(tp->name, "cone"))
			d = ft_cone(all, tp);
		else if (ft_strequ(tp->name, "barrel"))
			d = ft_barrel(all, tp);
		if (d >= 0.0)
		{
			if (all->d < 0.0)
			{
				all->d = d;
				color = tp->p2;
			}
			if (d < all->d)
			{
				all->d = d;
				color = tp->p2;
			}
		}
		tp = tp->next;
	}
//	printf("[%.4f]\n", all->d);
	if (all->d >= 0.0)
	{
		mlx_pixel_put(all->ptr.mlx, all->ptr.win, x, y, color);
	}
}
