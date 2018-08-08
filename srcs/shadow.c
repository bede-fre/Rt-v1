/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/08/08 17:43:47 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_mat3	ft_start_norm_p(t_shadow *shad, t_scene *tp)
{
	t_mat3	p;

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
	else
	{
		p.x = shad->p.x - tp->px;
		p.y = shad->p.y - tp->py;
		p.z = shad->p.z - tp->pz;
		p = ft_normalize(p);
	}
	return (p);
}

static void		ft_init_vect(t_all *all, t_shadow *shad, t_scene *tp, double d)
{
	shad->p.x = all->cam->px + all->univ_cam.x * d;
	shad->p.y = all->cam->py + all->univ_cam.y * d;
	shad->p.z = all->cam->pz + all->univ_cam.z * d;
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

int				ft_shadow_object(t_all *all, t_scene *tp, double d)
{
	t_shadow	shad;

	ft_init_vect(all, &shad, tp, d);
	shad.angle = (shad.uni_norme.x * shad.uni_light.x + shad.uni_norme.y
		* shad.uni_light.y + shad.uni_norme.z * shad.uni_light.z)
		/ (ft_vect_dist(shad.uni_norme) * ft_vect_dist(shad.uni_light));
	shad.angle = (shad.angle < 0.0 && ft_strequ(tp->name, "plane") == 0) ? 0.0 :
		shad.angle;
	shad.angle = (ft_strequ(tp->name, "plane")) ? ft_fabs(shad.angle) :
		shad.angle;
	shad.angle = (shad.angle * (shad.spot->p1 / 100.0))
		* ft_shadow_proj(all, tp, &shad);
	return (ft_rgba(tp->p1 * shad.angle, tp->p2 * shad.angle,
		tp->p3 * shad.angle, 0));
}
