/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 12:49:57 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/27 11:55:54 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

t_scene		*ft_find_link(t_scene *scene, char name[], int i)
{
	t_scene	*tp;

	tp = scene;
	while (tp)
	{
		if (ft_strequ(tp->name, name) && --i == 0)
			return (tp);
		tp = tp->next;
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
	all->pointpos.x = (-PLAN_W / 2.0) + 0.5 * INCR_X + x * INCR_X;
	all->pointpos.y = -((-PLAN_H / 2.0) + 0.5 * INCR_Y + y * INCR_Y);
	all->pointpos.z = 0.0;
	printf("[%.4f %.4f %.4f]\n", all->pointpos.x - all->campos.x, all->pointpos.y - all->campos.y, all->pointpos.z - all->campos.z);
}

void		ft_ray_tracing(t_all *all, int x, int y)
{
	ft_init_values(all);
	ft_find_coord_pixel(all, x, y);
}
