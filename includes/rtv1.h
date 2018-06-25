/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/06/25 15:36:35 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define TAGS_LIST_LEN		10
# define TAG_LEN			12
# define COL_LEN			12
# define VIEWPLANEDIST		1.0
# define VIEWPLANEHEIGHT	0.35
# define VIEWPLANEWIDTH		0.5

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

typedef struct		s_scene
{
	char			*name;
	int				px;
	int				py;
	int				pz;
	int				dx;
	int				dy;
	int				dz;
	int				p1;
	int				p2;
	int				p3;
	int				p4;
	int				p5;
	struct s_scene	*next;
}					t_scene;

typedef struct		s_all
{
//	t_mlx			mlx;
	t_scene			scene;
	char			tags_lst[TAGS_LIST_LEN][TAG_LEN];
}					t_all;

void				ft_parse_csv(char *xml, t_all *all);

#endif
