/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/18 10:21:45 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_sphere(t_all *all, t_scene *tp)
{
	t_equ	p;

	p.a = pow(all->univect.x, 2.0) + pow(all->univect.y, 2.0) +
		pow(all->univect.z, 2.0);
	p.b = (all->univect.x * (all->campos.x - (double)tp->px) + all->univect.y *
		(all->campos.y - (double)tp->py) + all->univect.z *
		(all->campos.z - (double)tp->pz)) * 2.0;
	p.c = (pow(all->campos.x - (double)tp->px, 2.0) +
		(pow(all->campos.y - (double)tp->py, 2.0) +
		pow(all->campos.z - (double)all->scene.pz, 2.0)) -
		pow((double)tp->p4, 2.0));
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
	if (p.d > 0)
	{
		p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
		p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
		return ((p.t1 < p.t2) ? p.t1 : p.t2);
	}
	return ((p.d == 0) ? p.t1 = -p.b / (2.0 * p.a) : -1);
}

double	ft_plane(t_all *all, t_scene *tp)
{
	double	t;

	t = -((((double)tp->px * (all->campos.x - all->pointpos.x))
		+ ((double)tp->py * (all->campos.y - all->pointpos.y))
		+ ((double)tp->pz * (all->campos.z - all->pointpos.z))
		+ (double)tp->p4) / (((double)tp->px * all->univect.x)
		+ ((double)tp->py * all->univect.y)
		+ ((double)tp->pz * all->univect.z)));
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
	t_equ	p;

	p.a = pow(all->univect.x, 2.0) + pow(all->univect.y, 2.0);
	p.b = 2.0 * (all->univect.x * (all->campos.x - (double)tp->px)
		+ all->univect.y * (all->campos.y - (double)tp->py));
	p.c = (pow(all->campos.x - (double)tp->px, 2.0)
		+ (pow(all->campos.y - (double)tp->py, 2.0)) - pow((double)tp->p4, 2.0));
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
	p.t1 = 0;
	p.t2 = 0;
	if (p.d > 0)
	{
		p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
		p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
		if (p.t1 < 0.0 || p.t2 < 0.0)
			return (-1.0);
		if (p.t1 > p.t2)
			return (p.t1);
		else
			return (p.t2);
	}
	else if (p.d == 0)
	{
		p.t1 = -p.b / (2.0 * p.a);
		return (p.t1);
	}
	else
		return (-1.0);
}
