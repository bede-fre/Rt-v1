/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:06:17 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/11 10:48:38 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_print_link(t_scene *tp)
{
	int	i;

	ft_putstr(tp->name);
	i = 1;
	while (++i <= COL_LEN)
	{
		ft_putchar(';');
		ft_putnbr(*((int*)tp + i));
	}
	ft_putchar('\n');
}

static void	ft_free_lst(t_scene *scene)
{
	t_scene	*tp;

	ft_print_link(scene);
	ft_memdel((void **)&scene->name);
	scene = scene->next;
	while (scene)
	{
		ft_print_link(scene);
		tp = scene->next;
		ft_memdel((void **)&scene->name);
		ft_memdel((void **)&scene);
		scene = tp;
	}
}

static void	ft_init_elem_lst(t_all *all)
{
	int			i;
	const char	elem_lst[ELEM_LIST_LEN][ELEM_LEN] = {"cam", "spot", "plane",
		"sphere", "cone", "cylinder"};

	i = -1;
	while (++i < ELEM_LIST_LEN)
		ft_strcpy(all->elem_lst[i], elem_lst[i]);
}

int			main(int ac, char **av)
{
	t_all	all;
	int		i;

	i = ft_strlen(av[1]);
	if (ac != 2 || av[1][i - 1] != 'v' || av[1][i - 2] != 's' ||
			av[1][i - 3] != 'c' || av[1][i - 4] != '.')
		ft_error("usage: ./rtv1 [scene.csv]", 1, ft_puterror);
	ft_init_elem_lst(&all);
	ft_parse_csv(av[1], &all);
	ft_draw(all);
	ft_free_lst(&all.scene);
	return (0);
}
