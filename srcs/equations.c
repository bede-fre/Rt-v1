/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/08/08 17:22:53 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rot	ft_rotation(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_rot	new;

	new.uni.x = uni->x;
	new.uni.y = uni->y;
	new.uni.z = uni->z;
	new.uni = ft_rot_x(new.uni, ft_rad(-(double)tp->dx));
	new.uni = ft_rot_y(new.uni, ft_rad(-(double)tp->dy));
	new.uni = ft_rot_z(new.uni, ft_rad(-(double)tp->dz));
	new.pos.x = pos->x - tp->px;
	new.pos.y = pos->y - tp->py;
	new.pos.z = pos->z - tp->pz;
	new.pos = ft_rot_x(new.pos, ft_rad(-(double)tp->dx));
	new.pos = ft_rot_y(new.pos, ft_rad(-(double)tp->dy));
	new.pos = ft_rot_z(new.pos, ft_rad(-(double)tp->dz));
	new.pos.x += tp->px;
	new.pos.y += tp->py;
	new.pos.z += tp->pz;
	return (new);
}

double			ft_sphere(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
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

double			ft_plane(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	double	t;

	t = -(((tp->univect.x * (pos->x - tp->px))
		+ (tp->univect.y * (pos->y - tp->py))
		+ (tp->univect.z * (pos->z - tp->pz))
		+ (double)tp->p4) /
		((tp->univect.x * uni->x)
		+ (tp->univect.y * uni->y)
		+ (tp->univect.z * uni->z)));
	return (t);
}

double			ft_cone(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_rot	new;
	t_equ	p;

	new = ft_rotation(tp, uni, pos);
	p.a = pow(new.uni.x, 2.0) -
		(pow(new.uni.y, 2.0) * tan(ft_rad((double)tp->p4))) +
		pow(new.uni.z, 2.0);
	p.b = ((new.uni.x * (new.pos.x - (double)tp->px)) -
		((new.uni.y * (new.pos.y - (double)tp->py)) *
		tan(ft_rad((double)tp->p4))) +
		(new.uni.z * (new.pos.z - (double)tp->pz))) * 2.0;
	p.c = (pow(new.pos.x - (double)tp->px, 2.0)) -
		((pow(new.pos.y - (double)tp->py, 2.0)) * tan(ft_rad((double)tp->p4))) +
		(pow(new.pos.z - (double)tp->pz, 2.0));
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

double			ft_cylinder(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_rot	new;
	t_equ	p;

	new = ft_rotation(tp, uni, pos);
	p.a = pow(new.uni.x, 2.0) + pow(new.uni.z, 2.0);
	p.b = ((new.uni.x * (new.pos.x - (double)tp->px)) +
			(new.uni.z * (new.pos.z - (double)tp->pz))) * 2.0;
	p.c = ((pow(new.pos.x - (double)tp->px, 2.0)) +
			(pow(new.pos.z - (double)tp->pz, 2.0))) -
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
