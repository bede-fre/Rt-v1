/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/04 17:28:16 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mat3	ft_shadow_cone(t_shadow *shad, t_scene tp)
{
	t_mat3	p;
	t_mat3	u;
	double	d;

	u.x = shad->p.x - tp.px;
	u.y = shad->p.y - tp.py;
	u.z = shad->p.z - tp.pz;
	d = ft_vect_dist(u);
	d /= cos(ft_rad((!tp.univect.y) ? tp.p4 + (180.0 - 2.0 * tp.p4) : tp.p4));
	tp.univect.x = (tp.univect.x * d) + tp.px;
	tp.univect.y = (tp.univect.y * d) + tp.py;
	tp.univect.z = (tp.univect.z * d) + tp.pz;
	p.x = shad->p.x - tp.univect.x;
	p.y = shad->p.y - tp.univect.y;
	p.z = shad->p.z - tp.univect.z;
	p = ft_normalize(p);
	return (p);
}

static t_mat3	ft_shadow_cylinder(t_shadow *shad, t_scene tp)
{
	t_mat3	p;
	t_mat3	u;
	double	a;
	double	b;

	u.x = shad->p.x - tp.px;
	u.y = shad->p.y - tp.py;
	u.z = shad->p.z - tp.pz;
	a = u.x * tp.univect.x + u.y * tp.univect.y + u.z * tp.univect.z;
	b = pow(tp.univect.x, 2.0) +
		pow(tp.univect.y, 2.0) +
		pow(tp.univect.z, 2.0);
	tp.univect.x = (a * tp.univect.x / b) + tp.px;
	tp.univect.y = (a * tp.univect.y / b) + tp.py;
	tp.univect.z = (a * tp.univect.z / b) + tp.pz;
	p.x = shad->p.x - tp.univect.x;
	p.y = shad->p.y - tp.univect.y;
	p.z = shad->p.z - tp.univect.z;
	p = ft_normalize(p);
	return (p);
}

t_mat3			ft_start_norm_p(t_shadow *shad, t_scene tp)
{
	t_mat3	p;

	if (ft_strequ(tp.name, "sphere"))
	{
		p.x = shad->p.x - tp.px;
		p.y = shad->p.y - tp.py;
		p.z = shad->p.z - tp.pz;
		p = ft_normalize(p);
	}
	else if (ft_strequ(tp.name, "cylinder"))
		p = ft_shadow_cylinder(shad, tp);
	else if (ft_strequ(tp.name, "cone"))
		p = ft_shadow_cone(shad, tp);
	else
	{
		p.x = tp.univect.x;
		p.y = tp.univect.y;
		p.z = tp.univect.z;
		p = ft_normalize(p);
	}
	return (p);
}

static double	ft_shadow_proj(t_all *all, t_scene *tp, t_shadow *shad)
{
	t_funct	f;
	t_scene	*tmp;
	double	d;

	d = 0.0;
	tmp = &all->scene;
	while (tmp)
	{
		if (tmp != tp)
			if ((f = ft_get_funct(tmp->name)))
			{
				d = f(tmp, &shad->uni_light2, &shad->p2);
				if (d >= 0.0 && floor(d) <= shad->d)
					return (0.5);
			}
		tmp = tmp->next;
	}
	return (1.0);
}

int				ft_shadow_object(t_all *all, t_scene *tp)
{
	t_shadow	shad;

	ft_init_vect(all, &shad, tp);
	shad.angle = ft_dot_product(shad.uni_norme, shad.uni_light) /
		(ft_vect_dist(shad.uni_norme) * ft_vect_dist(shad.uni_light));
	if (all->test)
		printf("angle: %f\n", acos(shad.angle));
	shad.angle = (ft_strequ(tp->name, "plane")) ? ft_fabs(shad.angle) :
		shad.angle;
	shad.angle = (shad.angle < 0.0) ? 0.0 : shad.angle;
	shad.angle = (shad.angle * (shad.spot->p1 / 100.0))
		* ft_shadow_proj(all, tp, &shad);
	return (ft_rgba((unsigned char)(tp->p1 * shad.angle),
		(unsigned char)(tp->p2 * shad.angle),
		(unsigned char)(tp->p3 * shad.angle), (unsigned char)0));
}
