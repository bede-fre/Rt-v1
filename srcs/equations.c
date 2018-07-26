/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/26 15:56:27 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_sphere(t_all *all, t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

	(void)all;
	p.a = pow(uni->x, 2.0) + pow(uni->y, 2.0) + pow(uni->z, 2.0);
	p.b = (uni->x * (pos->x - (double)tp->px) +
		uni->y * (pos->y - (double)tp->py) +
		uni->z * (pos->z - (double)tp->pz)) * 2.0;
	p.c = (pow(pos->x - (double)tp->px, 2.0) +
		pow(pos->y - (double)tp->py, 2.0) +
		pow(pos->z - (double)tp->pz, 2.0)) -
		pow((double)tp->p4, 2.0);
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
	if (p.d < 0.0)
		return (-1.0);
	p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
	p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
	if (p.t1 < 0.0 && p.t2 < 0.0)
		return (-1.0);
	if (p.t1 >= 0.0 && p.t2 >= 0.0)
		return ((p.t1 < p.t2) ? p.t1 : p.t2);
	else
		return ((p.t1 >= 0.0) ? p.t1 : p.t2);
}

double	ft_plane(t_all *all, t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	double	t;

	(void)all;
	t = -((((double)tp->dx * (pos->x - tp->px))
		+ ((double)tp->dy * (pos->y - tp->py))
		+ ((double)tp->dz * (pos->z - tp->pz))
		+ (double)tp->p4) /
		(((double)tp->dx * uni->x)
		+ ((double)tp->dy * uni->y)
		+ ((double)tp->dz * uni->z)));
	if (t != 0.0)
		return (t);
	else
		return (-1.0);
}

double	ft_cone(t_all *all, t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

	(void)all;
	p.a = pow(uni->x, 2.0) -
		pow(uni->y, 2.0) +
		pow(uni->z, 2.0);
	p.b = ((uni->x * (pos->x - (double)tp->px)) +
		(uni->z * (pos->z - (double)tp->pz)) -
		(uni->y * (pos->y - (double)tp->py) * pow(tan(ft_rad((double)tp->p4)), 2.0))) * 2.0;
	p.c = ((pow(pos->x - (double)tp->px, 2.0)) +
		(pow(pos->z - (double)tp->pz, 2.0)) -
		(pow(pos->y - (double)tp->py, 2.0) * pow(tan(ft_rad((double)tp->p4)), 2.0)));
	if (all->test == 1)
		printf("%f\n", pow(pos->y - (double)tp->py, 2.0) * pow(tan(ft_rad((double)tp->p4)), 2.0));
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
	if (p.d < 0.0)
		return (-1.0);
	p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
	p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
	if (p.t1 < 0.0 && p.t2 < 0.0)
		return (-1.0);
	if (p.t1 >= 0.0 && p.t2 >= 0.0)
		return ((p.t1 < p.t2) ? p.t1 : p.t2);
	else
		return ((p.t1 >= 0.0) ? p.t1 : p.t2);
}

double	ft_cylinder(t_all *all, t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

	(void)all;
	p.a = pow(uni->x, 2.0) * (double)tp->dx +
		pow(uni->y, 2.0) * (double)tp->dy +
		pow(uni->z, 2.0) * (double)tp->dz;
	p.b = ((uni->x * (pos->x - (double)tp->px)) * (double)tp->dx +
		(uni->y * (pos->y - (double)tp->py)) * (double)tp->dy +
		(uni->z * (pos->z - (double)tp->pz)) * (double)tp->dz) * 2.0;
	p.c = ((pow(pos->x - (double)tp->px, 2.0)) * (double)tp->dx +
		(pow(pos->y - (double)tp->py, 2.0)) * (double)tp->dy +
		(pow(pos->z - (double)tp->pz, 2.0)) * (double)tp->dz) -
		pow((double)tp->p4, 2.0);
	p.d = pow(p.b, 2.0) - 4.0 * p.a * p.c;
	if (p.d < 0.0)
		return (-1.0);
	p.t1 = (-p.b + sqrt(p.d)) / (2.0 * p.a);
	p.t2 = (-p.b - sqrt(p.d)) / (2.0 * p.a);
	if (p.t1 < 0.0 && p.t2 < 0.0)
		return (-1.0);
	if (p.t1 >= 0.0 && p.t2 >= 0.0)
		return ((p.t1 < p.t2) ? p.t1 : p.t2);
	else
		return ((p.t1 >= 0.0) ? p.t1 : p.t2);
}
