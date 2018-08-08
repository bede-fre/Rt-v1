/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:39:47 by lguiller          #+#    #+#             */
/*   Updated: 2018/08/08 10:22:58 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

t_mat3	ft_rot_x(t_mat3 v, double a)
{
	t_mat3	w;
	double	y;
	double	z;

	y = v.y;
	z = v.z;
	w.x = v.x;
	w.y = y * cos(a) - z * sin(a);
	w.z = y * sin(a) + z * cos(a);
	return (w);
}

t_mat3	ft_rot_y(t_mat3 v, double a)
{
	t_mat3	w;
	double	x;
	double	z;

	x = v.x;
	z = v.z;
	w.x = x * cos(a) + z * sin(a);
	w.y = v.y;
	w.z = -x * sin(a) + z * cos(a);
	return (w);
}

t_mat3	ft_rot_z(t_mat3 v, double a)
{
	t_mat3	w;
	double	x;
	double	y;

	x = v.x;
	y = v.y;
	w.x = x * cos(a) - y * sin(a);
	w.y = x * sin(a) + y * cos(a);
	w.z = v.z;
	return (w);
}
