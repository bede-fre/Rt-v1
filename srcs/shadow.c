/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/08/09 16:59:35 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mat3	ft_start_norm_p(t_shadow *shad, t_scene *tp)
{
	t_mat3	p;
	t_mat3	u;
	t_mat3	v;
	double	a;
	double	b;

	if (ft_strequ(tp->name, "sphere") == 1)
	{
		p.x = shad->p.x - tp->px;
		p.y = shad->p.y - tp->py;
		p.z = shad->p.z - tp->pz;
		p = ft_normalize(p);
	}
	else if (ft_strequ(tp->name, "plane") == 1)
	{
		p.x = tp->univect.x;
		p.y = tp->univect.y;
		p.z = tp->univect.z;
		p = ft_normalize(p);
	}
	else if (ft_strequ(tp->name, "cylinder") == 1 || ft_strequ(tp->name, "cone"))
	{
		u.x = shad->p.x - tp->px;
		u.y = shad->p.y - tp->py;
		u.z = shad->p.z - tp->pz;
		v.x = 0.0;
		v.y = 1.0;
		v.z = 0.0;
		v = ft_rot_x(v, ft_rad(tp->dx));
		v = ft_rot_y(v, ft_rad(tp->dy));
		v = ft_rot_z(v, ft_rad(tp->dz));
		a = u.x * v.x + u.y * v.y + u.z * v.z;
		b = pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0);
		v.x = (a * v.x / b) + tp->px;
		v.y = (a * v.y / b) + tp->py;
		v.z = (a * v.z / b) + tp->pz;
		p.x = shad->p.x - v.x;
		p.y = shad->p.y - v.y;
		p.z = shad->p.z - v.z;
		p = ft_normalize(p);
	}
	else
	{
		p.x = shad->p.x - tp->px;
		p.y = shad->p.y - tp->py;
		p.z = shad->p.z - tp->pz;
		p = ft_normalize(p);
	}
	return (p);
}

static void		ft_init_vect(t_all *all, t_shadow *shad, t_scene *tp)
{
	shad->p.x = all->univ_cam.x * all->d + all->cam->px;
	shad->p.y = all->univ_cam.y * all->d + all->cam->py;
	shad->p.z = all->univ_cam.z * all->d + all->cam->pz;
	shad->uni_norme = ft_start_norm_p(shad, tp);
	shad->uni_light.x = all->spot->px - shad->p.x;
	shad->uni_light.y = all->spot->py - shad->p.y;
	shad->uni_light.z = all->spot->pz - shad->p.z;
	shad->spot = ft_find_link(&all->scene, "spot", 1);
	shad->d = sqrt(pow(shad->uni_light.x, 2.0) + pow(shad->uni_light.y, 2.0) +
		pow(shad->uni_light.z, 2.0));
	shad->uni_light = ft_normalize(shad->uni_light);
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
				d = f(tmp, &shad->uni_light, &shad->p);
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
	shad.angle = (shad.uni_norme.x * shad.uni_light.x + shad.uni_norme.y
		* shad.uni_light.y + shad.uni_norme.z * shad.uni_light.z);
	if (all->test == 1)
		printf("%f\n", acos(shad.angle));
	shad.angle = (shad.angle < 0.0 && ft_strequ(tp->name, "plane") == 0) ? 0.0 :
		shad.angle;
	shad.angle = (ft_strequ(tp->name, "plane")) ? ft_fabs(shad.angle) :
		shad.angle;
	shad.angle = (shad.angle * (shad.spot->p1 / 100.0))
		* ft_shadow_proj(all, tp, &shad);
	return (ft_rgba((unsigned char)(tp->p1 * shad.angle),
		(unsigned char)(tp->p2 * shad.angle),
		(unsigned char)(tp->p3 * shad.angle), (unsigned char)0));
}
