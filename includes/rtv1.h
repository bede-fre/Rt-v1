/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/06/21 15:55:39 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define TAGS_LIST_LEN	10
# define TAG_LEN		12
# define COL_LEN		8

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

typedef struct		s_scene
{
	char			*name;
	t_coord			pos;
	t_coord			dir;
	int				param1;
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
