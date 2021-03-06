/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2019/01/23 14:16:45 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_rot			ft_rotation(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_rot	new;

	if (uni)
	{
		new.uni.x = uni->x;
		new.uni.y = uni->y;
		new.uni.z = uni->z;
		new.uni = ft_vecrotx(new.uni, ft_rad(-tp->dx));
		new.uni = ft_vecroty(new.uni, ft_rad(-tp->dy));
		new.uni = ft_vecrotz(new.uni, ft_rad(-tp->dz));
	}
	new.pos.x = pos->x - tp->px;
	new.pos.y = pos->y - tp->py;
	new.pos.z = pos->z - tp->pz;
	new.pos = ft_vecrotx(new.pos, ft_rad(-tp->dx));
	new.pos = ft_vecroty(new.pos, ft_rad(-tp->dy));
	new.pos = ft_vecrotz(new.pos, ft_rad(-tp->dz));
	new.pos.x += tp->px;
	new.pos.y += tp->py;
	new.pos.z += tp->pz;
	return (new);
}

double			ft_sphere(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_equ	p;

	p.a = pow(uni->x, 2.0) + pow(uni->y, 2.0) + pow(uni->z, 2.0);
	p.b = (uni->x * (pos->x - tp->px) +
		uni->y * (pos->y - tp->py) +
		uni->z * (pos->z - tp->pz)) * 2.0;
	p.c = (pow(pos->x - tp->px, 2.0) +
		pow(pos->y - tp->py, 2.0) +
		pow(pos->z - tp->pz, 2.0)) -
		pow(tp->p4, 2.0);
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
	t_rot	new;
	double	t;

	new = ft_rotation(tp, uni, pos);
	t = -(((tp->univect.x * (new.pos.x - tp->px))
		+ (tp->univect.y * (new.pos.y - tp->py))
		+ (tp->univect.z * (new.pos.z - tp->pz))
		+ tp->p4) /
		((tp->univect.x * new.uni.x)
		+ (tp->univect.y * new.uni.y)
		+ (tp->univect.z * new.uni.z)));
	return (t);
}

double			ft_cone(t_scene *tp, t_mat3 *uni, t_mat3 *pos)
{
	t_rot	new;
	t_equ	p;

	new = ft_rotation(tp, uni, pos);
	p.a = pow(new.uni.x, 2.0) -
		(pow(new.uni.y, 2.0) * tan(ft_rad(tp->p4))) +
		pow(new.uni.z, 2.0);
	p.b = ((new.uni.x * (new.pos.x - tp->px)) -
		((new.uni.y * (new.pos.y - tp->py)) *
		tan(ft_rad(tp->p4))) +
		(new.uni.z * (new.pos.z - tp->pz))) * 2.0;
	p.c = (pow(new.pos.x - tp->px, 2.0)) -
		((pow(new.pos.y - tp->py, 2.0)) * tan(ft_rad(tp->p4))) +
		(pow(new.pos.z - tp->pz, 2.0));
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
	p.b = ((new.uni.x * (new.pos.x - tp->px)) +
		(new.uni.z * (new.pos.z - tp->pz))) * 2.0;
	p.c = ((pow(new.pos.x - tp->px, 2.0)) +
		(pow(new.pos.z - tp->pz, 2.0))) -
		pow(tp->p4, 2.0);
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
