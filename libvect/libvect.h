/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:36:45 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/26 15:55:23 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECT_H
# define LIBVECT_H

# include <math.h>

typedef struct		s_mat3
{
	double			x;
	double			y;
	double			z;
}					t_mat3;

void				ft_rot_x(t_mat3 *v, double a);
void				ft_rot_y(t_mat3 *v, double a);
void				ft_rot_z(t_mat3 *v, double a);

#endif
