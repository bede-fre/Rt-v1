/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/06/27 09:58:15 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define ELEM_LIST_LEN	6
# define ELEM_LEN		10
# define COL_LEN		12
# define PLAN_D			10.0
# define PLAN_W			24.0
# define PLAN_H			18.0
# define WIN_X			768
# define WIN_Y			576
# define INCR_X			PLAN_W / (double)WIN_X
# define INCR_Y			PLAN_H / (double)WIN_Y

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct		s_gnl
{
	int				fd;
	int				x;
	char			*line;
}					t_gnl;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_coord_2d
{
	int				x;
	int				y;
}					t_coord_2d;

typedef struct		s_coord_3d
{
	double			x;
	double			y;
	double			z;
}					t_coord_3d;

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
	t_mlx			ptr;
	t_scene			scene;
	t_coord_2d		mouse;
	t_coord_3d		campos;
	t_coord_3d		pointpos;
	t_coord_3d		normpos;
	char			elem_lst[ELEM_LIST_LEN][ELEM_LEN];
}					t_all;

void				ft_parse_csv(char *xml, t_all *all);
t_scene				*ft_find_link(t_scene *scene, char name[], int i);
void				ft_draw(t_all all);
void				ft_init_mlx(t_all *all);
void				ft_ray_tracing(t_all *all);

#endif
