/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/09/06 16:17:50 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include "libvect.h"
# include <math.h>

# define ELEM_LIST_LEN	6
# define ELEM_LEN		10
# define COL_LEN		12
# define PLAN_D			1.0
# define PLAN_W			2.0
# define PLAN_H			2.0
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
	void			*img;
	char			*data;
	int				bpp;
	int				endian;
	int				sl;
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

typedef struct		s_equ
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			t1;
	double			t2;
}					t_equ;

typedef struct		s_scene
{
	char			*name;
	double			px;
	double			py;
	double			pz;
	double			dx;
	double			dy;
	double			dz;
	double			p1;
	double			p2;
	double			p3;
	double			p4;
	double			p5;
	t_mat3			univect;
	struct s_scene	*next;
}					t_scene;

typedef struct		s_shadow
{
	t_mat3			p;
	t_mat3			p2;
	t_mat3			uni_light;
	t_mat3			uni_light2;
	t_mat3			uni_norme;
	t_scene			*spot;
	double			angle;
	double			d;
}					t_shadow;

typedef struct		s_all
{
	t_mlx			ptr;
	t_scene			scene;
	t_scene			*cam;
	t_scene			*spot;
	t_coord_2d		mouse;
	t_mat3			pos_cam;
	t_mat3			uni_cam;
	t_mat3			pos_spot;
	char			elem_lst[ELEM_LIST_LEN][ELEM_LEN];
	double			d;
	int				test;
}					t_all;

typedef double		(*t_funct)(t_scene*, t_mat3*, t_mat3*);

typedef struct		s_rt
{
	t_scene			*tp;
	t_scene			*good;
	int				color;
	int				first;
}					t_rt;

typedef struct		s_rot
{
	t_mat3			uni;
	t_mat3			pos;
}					t_rot;

void				ft_parse_csv(char *xml, t_all *all);
void				ft_fill_pixel(t_mlx *mlx, int x, int y, int col);
t_scene				*ft_find_link(t_scene *scene, char name[]);
t_funct				ft_get_funct(char *name);
void				ft_draw(t_all all);
void				ft_init_mlx(t_all *all);
void				ft_ray_tracing(t_all *all, int x, int y);
int					ft_key_press(int key, void *p);
int					ft_button_press(int button, int x, int y, t_all *all);
int					ft_shadow_object(t_all *all, t_scene *tp);
double				ft_sphere(t_scene *tp, t_mat3 *uni, t_mat3 *pos);
double				ft_plane(t_scene *tp, t_mat3 *uni, t_mat3 *pos);
double				ft_cone(t_scene *tp, t_mat3 *uni, t_mat3 *pos);
double				ft_cylinder(t_scene *tp, t_mat3 *uni, t_mat3 *pos);
t_rot				ft_rotation(t_scene *tp, t_mat3 *uni, t_mat3 *pos);
void				ft_init_elem_lst(t_all *all);
void				ft_init_values(t_all *all, t_rt *rt);
void				ft_init_vect(t_all *all, t_shadow *shad, t_scene *tp);
t_mat3				ft_start_norm_p(t_shadow *shad, t_scene tp);
double				ft_specular_light(t_mat3 spot, t_mat3 inter, t_mat3 norm, t_mat3 cam);

#endif
