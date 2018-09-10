/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:14:09 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/10 09:27:48 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_specular_light(t_mat3 spot, t_mat3 inter, t_mat3 norm, t_mat3 cam)
{
	double	angle;
	t_mat3	spot_int;
	t_mat3	int_cam;
	t_mat3	int_ref;

	spot_int.x = inter.x - spot.x;
	spot_int.y = inter.y - spot.y;
	spot_int.z = inter.z - spot.z;
	spot_int = ft_normalize(spot_int);
	int_cam.x = cam.x - inter.x;
	int_cam.y = cam.y - inter.y;
	int_cam.z = cam.z - inter.z;
	int_cam = ft_normalize(int_cam);
	int_ref.x = spot_int.x - 2.0 * norm.x * ft_dot_product(norm, spot_int);
	int_ref.y = spot_int.y - 2.0 * norm.y * ft_dot_product(norm, spot_int);
	int_ref.z = spot_int.z - 2.0 * norm.z * ft_dot_product(norm, spot_int);
	angle = ft_deg(acos(ft_dot_product(int_ref, int_cam)));
	return ((angle < 20.0) ?
		255.0 * pow(ft_dot_product(int_ref, int_cam), 75.0) : 0.0);
}
