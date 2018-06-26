/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/26 17:46:20 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

t_scene		*ft_find_link(t_scene *scene, char name[], int i)
{
	t_scene	*tp;

	tp = scene;
	while (tp)
	{
		if (ft_strequ(scene->name, name) && --i == 0)
			return (tp);
		tp = scene->next;
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
	all->pointpos.x = 0.5 * (-PLAN_W / 2.0 + INCR_X) + x * INCR_X;
	all->pointpos.y = 0.5 * (PLAN_H / 2.0 + INCR_Y) + y * INCR_Y;
	all->pointpos.z = 0.0;
}

void		ft_ray_tracing(t_all *all)
{
	ft_find_coord_pixel(all, 0, 0);
	ft_init_values(all);
}
