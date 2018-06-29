/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/29 17:30:45 by bede-fre         ###   ########.fr       */
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
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;

	ft_init_values(all);
	ft_find_coord_pixel(all, x, y);
	printf("[%.4f %.4f %.4f %.4f]\n", all->pointpos.x, all->pointpos.y, all->pointpos.z, all->lg);
	printf("[%.4f %.4f %.4f]\n", all->pointpos.x/all->lg, all->pointpos.y/all->lg, all->pointpos.z/ all->lg);
	a = pow(all->pointpos.x / all->lg, 2.0) + pow(all->pointpos.y / all->lg, 2.0)
		+ pow(all->pointpos.z / all->lg, 2.0);
	b = 2.0 * ((all->pointpos.x / all->lg) * (all->campos.x - (double)all->scene.px)
		+ (all->pointpos.y / all->lg) * (all->campos.y - (double)all->scene.py)
		+ (all->pointpos.z / all->lg) * (all->campos.z - (double)all->scene.pz));
	c = (pow(all->campos.x - (double)all->scene.px, 2.0)
		+ (pow(all->campos.y - (double)all->scene.py, 2.0) + pow(all->campos.z
		- (double)all->scene.pz, 2.0)) - pow((double)all->scene.p4, 2.0));
	printf("[%.4f %.4f %.4f]\n", a, b, c);
	printf("[%.4f]\n", (double)all->scene.p4);
	d = pow(b, 2.0) - 4.0 * a * c;
	t1 = 0;
	t2 = 0;
	if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		printf("t1: %.2f - t2: %.2f\n", t1, t2);
	}
	else if (d == 0)
	{
		t1 = -b / (2.0 * a);
		printf("t: %.2f\n", t1);
	}
	else
		printf("pas de solution reel\n");
}
