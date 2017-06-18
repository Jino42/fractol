/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 08:33:22 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/17 22:47:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	call_gnl(t_env *e, char **line, int fd)
{
	if (get_next_line(fd, line) != 1)
		end_of_program(e, "Erreur de parsing\n");
	if (!(*line))
		end_of_program(e, "Erreur de parsing\n");
}

static void parsing_part_2(t_env *e, char *line, int fd)
{
	char **str;
	char **str2;
	int	i;

	call_gnl(e, &line, fd);
	str = ft_strsplit(line, ' ');
	ft_strdel(&line);
	call_gnl(e, &line, fd);
	str2 = ft_strsplit(line, ' ');
	ft_strdel(&line);
	i = 0;
	while (str[i] && str2[i])
	{
		e->bud.min[i] = ft_atoi(str[i]);
		e->bud.max[i] = ft_atoi(str2[i]);
		ft_strdel(&str[i]);
		ft_strdel(&str2[i]);
		i++;
	}
	free(str);
	free(str2);
	if (i != 3)
		end_of_program(e, "Erreur de parsing, Zoom < 0\n");
}

static void	parsing_part_1(t_env *e, char *line, int fd)
{
	call_gnl(e, &line, fd);
	e->tool.iter = (long int)ft_atoi(line);
	if (e->tool.iter < 0)
		end_of_program(e, "Erreur de parsing\n");
	ft_strdel(&line);
	call_gnl(e, &line, fd);
	e->tool.zoom = ft_atoi(line);
		ft_strdel(&line);
	if (e->tool.zoom < 0)
		end_of_program(e, "Erreur de parsing\n");
	////////////Comparer au plan complexe ?
	call_gnl(e, &line, fd);
	e->tool.ajj_x = (V_PRECI)ft_atoi(line);
		ft_strdel(&line);
	call_gnl(e, &line, fd);
	e->tool.ajj_y = (V_PRECI)ft_atoi(line);
		ft_strdel(&line);
	call_gnl(e, &line, fd);
	e->bud.over = ft_atoi(line);
		ft_strdel(&line);
	if (e->bud.over < 1 || e->bud.over > 4)
		end_of_program(e, "Erreur de parsing, Over Bud [1-4]\n");
	call_gnl(e, &line, fd);
	e->bud.anti = ft_atoi(line);
		ft_strdel(&line);
	if (e->bud.anti < 0 || e->bud.anti > 1)
		end_of_program(e, "Erreur de parsing, Anti [0-1]\n");
	call_gnl(e, &line, fd);
	e->bud.gain = (float)ft_atoi(line) / 10;
		ft_strdel(&line);
	if (e->bud.gain < 0)
		end_of_program(e, "Erreur de parsing, Gain < 0\n");
}
/*
static void print_parsing(t_env *e, t_nc *nc)
{
	mvwprintw(nc->win, 15, 4, "Iter : [%i]", e->tool.iter);
	mvwprintw(nc->win, 16, 4, "Zoom : [%i]", e->tool.zoom);
	mvwprintw(nc->win, 17, 4, "X    : [%i]", 0);
	mvwprintw(nc->win, 18, 4, "Y    : [%i]", 0);
	mvwprintw(nc->win, 19, 4, "Over : [%i]", e->bud.over);
	mvwprintw(nc->win, 20, 4, "Anti : [%i]", e->bud.anti);
	mvwprintw(nc->win, 21, 4, "Gain : [%i]", e->bud.gain);
	mvwprintw(nc->win, 22, 4, "COLOR [MIN][MAX]");
	wattron(nc->win, COLOR_PAIR(NC_RED));
	mvwprintw(nc->win, 23, 4, "Red [%i][%i]", e->bud.min[2], e->bud.max[2]);
	wattroff(nc->win, COLOR_PAIR(NC_RED));
	wattron(nc->win, COLOR_PAIR(NC_GREEN));
	mvwprintw(nc->win, 24, 4, "Green [%i][%i]", e->bud.min[1], e->bud.max[1]);
	wattroff(nc->win, COLOR_PAIR(NC_GREEN));
	wattron(nc->win, COLOR_PAIR(NC_CYAN));
	mvwprintw(nc->win, 25, 4, "Blue [%i][%i]", e->bud.min[0], e->bud.max[0]);
	wattroff(nc->win, COLOR_PAIR(NC_CYAN));
}
*/
void		ncurses_parsing(t_env *e, t_nc *nc)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(e->name_preset[nc->cursor], O_RDONLY);
	if (!fd)
		end_of_program(e, "Erreur de fichier\n");
	parsing_part_1(e, line, fd);
	parsing_part_2(e, line, fd);
	close(fd);
	wrefresh(nc->win);
}