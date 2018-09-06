/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_csv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 10:42:35 by bede-fre          #+#    #+#             */
/*   Updated: 2018/09/06 11:42:36 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_infos(char **tab, t_scene *tp)
{
	int		i;

	tp->univect.x = 0.0;
	tp->univect.y = 1.0;
	tp->univect.z = 0.0;
	tp->name = ft_strdup(tab[0]);
	i = 0;
	while (tab[++i])
		*((double*)tp + i) = (double)ft_atoi(tab[i]);
	while (i++ < COL_LEN)
		*((double*)tp + i) = 0.0;
}

static void	ft_check_name(char *line, t_all *all, t_scene *tp)
{
	char	**tab;
	int		i;

	ft_remove_whitespaces(line);
	tab = ft_strsplit(line, ';');
	i = -1;
	while (++i < COL_LEN)
		if (ft_strequ(tab[0], all->elem_lst[i]))
			break ;
	if (!(ft_strequ(tab[0], all->elem_lst[i])))
		ft_error("error: invalid object name", 2, ft_puterror);
	ft_stock_infos(tab, tp);
	i = -1;
	while (tab[++i])
		ft_memdel((void **)&tab[i]);
	ft_memdel((void **)&tab);
}

void		ft_parse_csv(char *csv, t_all *all)
{
	t_gnl	gnl;
	t_scene	*tp;

	tp = &all->scene;
	if ((gnl.fd = open(csv, O_RDONLY)) == -1)
		ft_error("error", 1, perror);
	if ((gnl.x = get_next_line(gnl.fd, &gnl.line)) > 0)
		ft_check_name(gnl.line, all, tp);
	else
		ft_error("error: Not a valid file", 2, ft_puterror);
	ft_memdel((void **)&gnl.line);
	while ((gnl.x = get_next_line(gnl.fd, &gnl.line)) > 0)
	{
		if (!(tp->next = (t_scene*)ft_memalloc(sizeof(t_scene))))
			ft_error("error: Malloc", 1, ft_puterror);
		ft_check_name(gnl.line, all, tp->next);
		tp = tp->next;
		ft_memdel((void **)&gnl.line);
	}
	ft_memdel((void **)&gnl.line);
	tp->next = NULL;
	if (gnl.x == -1)
		ft_error("error: Not a valid file", 2, ft_puterror);
	if ((close(gnl.fd)) == -1)
		ft_error("error", 3, perror);
}
