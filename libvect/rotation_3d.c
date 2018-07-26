/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:39:47 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/26 15:46:53 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

void	ft_rot_x(t_mat3 *v, double a)
{
	v->y = v->y * cos(a) - v->z * sin(a);
	v->z = v->y * sin(a) + v->z * cos(a);
}

void	ft_rot_y(t_mat3 *v, double a)
{
	v->x = v->x * cos(a) + v->z * sin(a);
	v->z = -v->x * sin(a) + v->z * cos(a);
}

void	ft_rot_z(t_mat3 *v, double a)
{
	v->x = v->x * cos(a) - v->y * sin(a);
	v->y = v->x * sin(a) + v->y * cos(a);
}
