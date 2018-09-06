/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:14:09 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/06 18:20:49 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_specular_light(t_mat3 spot, t_mat3 inter, t_mat3 norm, t_mat3 cam)
{
	double	ret;
	double	angle;
	t_mat3	spot_inter;
	t_mat3	inter_cam;
	t_mat3	inter_ref;

	spot_inter.x = inter.x - spot.x;
	spot_inter.y = inter.y - spot.y;
	spot_inter.z = inter.z - spot.z;
	inter_cam.x = cam.x - inter.x;
	inter_cam.y = cam.y - inter.y;
	inter_cam.z = cam.z - inter.z;
//	inter_cam = ft_normalize(spot_inter);
	inter_ref.x = spot_inter.x - 2.0 * norm.x * ft_dot_product(norm, spot_inter);
	inter_ref.y = spot_inter.y - 2.0 * norm.y * ft_dot_product(norm, spot_inter);
	inter_ref.z = spot_inter.z - 2.0 * norm.z * ft_dot_product(norm, spot_inter);
	angle = acos(ft_dot_product(inter_ref, inter_cam) / (ft_vect_dist(inter_ref)
		* (ft_vect_dist(inter_cam)))) * 180.0/M_PI;
	if (angle < 40.0)
		ret = 255.0 * pow(ft_dot_product(inter_ref, inter_cam) /
			(ft_vect_dist(inter_ref) * ft_vect_dist(inter_cam)), 10.0);
	else
		ret = 0.0;

	return (ret);
}
