/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/16 11:07:33 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_sphere(t_all *all, t_scene *tp)
{
	t_equ	p;

	p.a = pow(all->pointpos.x / all->lg, 2.0) +
		pow(all->pointpos.y / all->lg, 2.0) +
		pow(all->pointpos.z / all->lg, 2.0);
	p.b = ((all->pointpos.x / all->lg) * (all->campos.x - (double)tp->px) +
		(all->pointpos.y / all->lg) * (all->campos.y - (double)tp->py) +
		(all->pointpos.z / all->lg) * (all->campos.z - (double)tp->pz)) * 2.0;
	p.c = (pow(all->campos.x - (double)tp->px, 2.0) +
		(pow(all->campos.y - (double)tp->py, 2.0) +
		pow(all->campos.z - (double)all->scene.pz, 2.0)) -
		pow((double)tp->p4, 2.0));
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
//	printf("[%.4f %.4f %.4f %.4f]\n", p.a, p.b, p.c, p.d);
	if (p.d > 0)
	{
		p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
		p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
		return ((p.t1 < p.t2) ? p.t1 : p.t2);
	}
	return ((p.d == 0) ? p.t1 = -p.b / (2.0 * p.a) : -1);
}

double	ft_plane(t_all *all)
{
	double	t;

	t = -((((double)all->scene.px * (all->campos.x - all->pointpos.x))
		+ ((double)all->scene.py * (all->campos.y - all->pointpos.y))
		+ ((double)all->scene.pz * (all->campos.z - all->pointpos.z))
		+ (double)all->scene.p3)
		/ (((double)all->scene.px * (all->pointpos.x / all->lg))
		+ ((double)all->scene.py * (all->pointpos.y / all->lg))
		+ ((double)all->scene.pz * (all->pointpos.z / all->lg))));
//	printf("[%.4f]\n", t);
	if (t > 0.0001)
		return (t);
	else
		return (-1.0);
}

double	ft_cone(t_all *all, t_scene *tp)
{
	(void)all;
	(void)tp;
	return (-1.0);
}

double	ft_cylinder(t_all *all, t_scene *tp)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;

	printf("[%.4f]\n", all->lg);
	a = pow(all->pointpos.x / all->lg, 2.0) + pow(all->pointpos.y / all->lg, 2.0);
	printf("pointpos[%.4f %.4f %.4f]\n", all->pointpos.x, all->pointpos.y, all->pointpos.z);
	printf("campos[%.4f %.4f %.4f]\n", all->campos.x, all->campos.y, all->campos.z);
	b = 2.0 * ((all->pointpos.x / all->lg) * (all->campos.x - (double)tp->px)
		+ (all->pointpos.y / all->lg) * (all->campos.y - (double)tp->py));
	c = (pow(all->campos.x - (double)tp->px, 2.0)
		+ (pow(all->campos.y - (double)tp->py, 2.0)) - pow((double)tp->p4, 2.0));
	d = pow(b, 2.0) - 4.0 * a * c;
	printf("[%.4f %.4f %.4f %.4f]\n", a, b, c, d);
	t1 = 0;
	t2 = 0;
	if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		printf("[%.4f - %.4f]\n", t1, t2);
		if (t1 < 0.0 || t2 < 0.0)
			return (-1.0);
		if (t1 > t2)
			return (t1);
		else
			return (t2);
	}
	else if (d == 0)
	{
		t1 = -b / (2.0 * a);
		printf("[%.4f]\n\n", t1);
		return (t1);
	}
	else
		return (-1.0);
}
