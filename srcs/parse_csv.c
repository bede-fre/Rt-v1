/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 10:42:35 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/21 14:05:42 by bede-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_print_link(t_scene *tp)
{
	ft_putstr(tp->name);
	ft_putchar(';');
	ft_putnbr(tp->pos.x);
	ft_putchar(';');
	ft_putnbr(tp->pos.y);
	ft_putchar(';');
	ft_putnbr(tp->pos.z);
	ft_putchar(';');
	ft_putnbr(tp->dir.x);
	ft_putchar(';');
	ft_putnbr(tp->dir.y);
	ft_putchar(';');
	ft_putnbr(tp->dir.z);
	ft_putchar(';');
	ft_putnbr(tp->param1);
	ft_putchar('\n');
}

static void	ft_stock_infos(char **tab, t_scene *tp)
{
	tp->name = ft_strdup(tab[0]);
	tp->pos.x = ft_atoi(tab[1]);
	tp->pos.y = ft_atoi(tab[2]);
	tp->pos.z = ft_atoi(tab[3]);
	tp->dir.x = ft_atoi(tab[4]);
	tp->dir.y = ft_atoi(tab[5]);
	tp->dir.z = ft_atoi(tab[6]);
	tp->param1 = ft_atoi(tab[7]);
}

static void	ft_check_name(char *line, t_all *all, t_scene *tp)
{
	char	**tab;
	int		i;

	i = 0;
	ft_remove_whitespaces(line);
	tab = ft_strsplit(line, ';');
	while (tab[i])
		i++;
	if (i != COL_LEN)
		ft_error("error: invalid column", 2, ft_puterror);
	i = -1;
	while (++i < COL_LEN)
		if (ft_strequ(tab[0], all->tags_lst[i]))
			break ;
	if (!(ft_strequ(tab[0], all->tags_lst[i])))
		ft_error("error: invalid object name", 2, ft_puterror);
	ft_stock_infos(tab, tp);
	i = -1;
	while (++i < COL_LEN)
		ft_memdel((void **)&tab[i]);
	ft_memdel((void **)&tab);
}

void		ft_parse_csv(char *csv, t_all *all)
{
	int		fd;
	int		gnl;
	char	*line;
	t_scene	*tp;
	int		i;

	i = -1;
	tp = &all->scene;
	if ((fd = open(csv, O_RDONLY)) == -1)
		ft_error("error", 1, perror);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		ft_check_name(line, all, tp);
		ft_print_link(tp);
		if (!(tp->next = (t_scene*)ft_memalloc(sizeof(t_scene))))
			ft_error("error: Malloc", 1, ft_puterror);
		tp = tp->next;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (gnl == -1)
		ft_error("error: Not a valid file", 2, ft_puterror);
	if ((close(fd)) == -1)
		ft_error("error", 3, perror);
}
