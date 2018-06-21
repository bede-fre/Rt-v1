/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:14:04 by lguiller          #+#    #+#             */
/*   Updated: 2018/06/21 10:07:29 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define TAGS_LIST_LEN	10
# define TAG_LEN		12

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

typedef struct		s_scene
{
	int				param1;
	char			*name;
	t_coord			pos;
	t_coord			dir;
	struct s_scene	*next;
}					t_scene;

typedef struct		s_all
{
//	t_mlx			mlx;
	t_scene			*scene;
	char			tags_lst[TAGS_LIST_LEN][TAG_LEN];
}					t_all;

void				ft_parse_csv(char *xml, t_all *all);

#endif
