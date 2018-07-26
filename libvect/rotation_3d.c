/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:39:47 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/26 16:43:18 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

void	ft_rot_x(t_mat3 *v, double a)
{
	double	y;
	double	z;

	y = v->y;
	z = v->z;
	v->y = y * cos(a) - z * sin(a);
	v->z = y * sin(a) + z * cos(a);
}

void	ft_rot_y(t_mat3 *v, double a)
{
	double	x;
	double	z;

	x = v->x;
	z = v->z;
	v->x = x * cos(a) + z * sin(a);
	v->z = -x * sin(a) + z * cos(a);
}

void	ft_rot_z(t_mat3 *v, double a)
{
	double	x;
	double	y;

	x = v->x;
	y = v->y;
	v->x = x * cos(a) - y * sin(a);
	v->y = x * sin(a) + y * cos(a);
}
