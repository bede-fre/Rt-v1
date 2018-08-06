/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/08/06 16:52:55 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_sphere(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

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

double	ft_plane(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	double	t;

	t = -(((tp->univect.x * (pos->x - tp->px))
		+ (tp->univect.y * (pos->y - tp->py))
		+ (tp->univect.z * (pos->z - tp->pz))
		+ (double)tp->p4) /
		((tp->univect.x * uni->x)
		+ (tp->univect.y * uni->y)
		+ (tp->univect.z * uni->z)));
	if (t != 0.0)
		return (t);
	else
		return (-1.0);
}

double	ft_cone(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

	p.a = pow(uni->x, 2.0) -
		pow(uni->y, 2.0) +
		pow(uni->z, 2.0);
	p.b = ((uni->x * (pos->x - (double)tp->px)) +
		(uni->z * (pos->z - (double)tp->pz)) -
		(uni->y * (pos->y - (double)tp->py) * pow(tan(ft_rad((double)tp->p4)), 2.0))) * 2.0;
	p.c = ((pow(pos->x - (double)tp->px, 2.0)) +
		(pow(pos->z - (double)tp->pz, 2.0)) -
		(pow(pos->y - (double)tp->py, 2.0) * pow(tan(ft_rad((double)tp->p4)), 2.0)));
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

double	ft_cylinder(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_mat3	v;
	t_equ	p;

	v.x = 1.0;
	v.y = 0.0;
	v.z = 1.0;
	p.a = pow(uni->x, 2.0) * v.x +
		pow(uni->y, 2.0) * v.y +
		pow(uni->z, 2.0) * v.z;
	p.b = ((uni->x * (pos->x - (double)tp->px)) * v.x +
		(uni->y * (pos->y - (double)tp->py)) * v.y +
		(uni->z * (pos->z - (double)tp->pz)) * v.z) * 2.0;
	p.c = ((pow(pos->x - (double)tp->px, 2.0)) * v.x +
		(pow(pos->y - (double)tp->py, 2.0)) * v.y +
		(pow(pos->z - (double)tp->pz, 2.0)) * v.z) -
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
