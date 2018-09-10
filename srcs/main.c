/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:06:17 by lguiller          #+#    #+#             */
/*   Updated: 2018/09/10 16:33:40 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_free_lst(t_scene *scene)
{
	t_scene	*tp;

	ft_memdel((void **)&scene->name);
	scene = scene->next;
	while (scene)
	{
		tp = scene->next;
		ft_memdel((void **)&scene->name);
		ft_memdel((void **)&scene);
		scene = tp;
	}
}

int			main(int ac, char **av)
{
	t_all	all;

	if (ac != 2)
		ft_error("usage: ./rtv1 [scene]", 1, ft_puterror);
	ft_init_elem_lst(&all);
	ft_parse_csv(av[1], &all);
	ft_draw(all);
	ft_free_lst(&all.scene);
	return (0);
}
