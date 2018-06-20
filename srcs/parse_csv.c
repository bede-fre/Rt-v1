/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 10:42:35 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/20 19:25:53 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_infos(char **tab, t_all *all)
{
	if (!(all->scene = (t_scene*)ft_memalloc(sizeof(t_scene))))
		exit(1);
	if (!(all->data = (t_scene*)ft_memalloc(sizeof(t_scene))))
		exit(1);
	data = all->scene;
	all->scene->name = tab[0];
	all->scene->pos.x = ft_atoi(tab[1]);
	all->scene->pos.y = ft_atoi(tab[2]);
	all->scene->pos.z = ft_atoi(tab[3]);
	all->scene->dir.x = ft_atoi(tab[4]);
	all->scene->dir.y = ft_atoi(tab[5]);
	all->scene->dir.z = ft_atoi(tab[6]);
	all->scene->param1 = ft_atoi(tab[7]);
}

static void	ft_check_name(char *line, t_all *all)
{
	char	**tab;
	int		i;

	i = -1;
	ft_remove_whitespaces(line);
	tab = ft_strsplit(line, ';');
	while (++i < TAGS_LIST_LEN)
		if (ft_strequ(tab[0], all->tags_lst[i]))
			break ;
	if (!(ft_strequ(tab[0], all->tags_lst[i])))
		ft_error("error: invalid object name", 2, ft_puterror);
	ft_stock_infos(tab, all);
	ft_memdel((void **)&tab);
}

void		ft_parse_csv(char *csv, t_all *all)
{
	int		fd;
	int		gnl;
	char	*line;

	if ((fd = open(csv, O_RDONLY)) == -1)
		ft_error("error", 1, perror);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		ft_check_name(line, all);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (gnl == -1)
		ft_error("error: Not a valid file", 2, ft_puterror);
	if ((close(fd)) == -1)
		ft_error("error", 3, perror);
}
