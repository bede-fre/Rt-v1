/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 10:06:17 by lguiller          #+#    #+#             */
/*   Updated: 2018/06/21 13:52:32 by bede-fre         ###   ########.fr       */
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

static void	ft_init_tags_lst(t_all *all)
{
	int			i;
	const char	tags_lst[TAGS_LIST_LEN][TAG_LEN] = {"cam", "spot", "plan",
		"sphere", "cone", "barrel", "position", "direction", "brightness",
		"color"};

	i = -1;
	while (++i < TAGS_LIST_LEN)
		ft_strcpy(all->tags_lst[i], tags_lst[i]);
}

int			main(int ac, char **av)
{
	t_all	all;
	int		i;

	i = ft_strlen(av[1]);
	if (ac != 2 || av[1][i - 1] != 'v' || av[1][i - 2] != 's' ||
		av[1][i - 3] != 'c' || av[1][i - 4] != '.')
		ft_error("usage: ./rtv1 [scene.csv]", 1, ft_puterror);
	ft_init_tags_lst(&all);
	ft_parse_csv(av[1], &all);
	ft_free_lst(&all.scene);
	return 0;
}
