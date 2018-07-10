/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/10 17:56:17 by bede-fre         ###   ########.fr       */
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
# define PLAN_D			1.0
# define PLAN_W			1.0
# define PLAN_H			1.0
# define WIN_X			800
# define WIN_Y			800
# define INCR_X			PLAN_W / (double)WIN_X
# define INCR_Y			PLAN_H / (double)WIN_Y

# ifdef __linux__
#  define ESC			65307
#  define L_CLIC		1
# else
#  define ESC			53
#  define L_CLIC		1
# endif

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
	double			lg;
	double			d;
}					t_all;

void				ft_parse_csv(char *xml, t_all *all);
t_scene				*ft_find_link(t_scene *scene, char name[], int i);
void				ft_draw(t_all all);
void				ft_init_mlx(t_all *all);
void				ft_ray_tracing(t_all *all, int x, int y);
int					ft_key_press(int key, void *p);
int					ft_button_press(int button, int x, int y, t_all *all);

#endif
