/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 07:12:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/07/10 22:15:43 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ncurses_key_move(t_env *e, t_nc *nc, int ret)
{
	(void)e;
	if (ret == KEY_DOWN)
	{
		if (!nc->menu_bud && nc->cursor < NB_FRACTAL - 1)
			nc->cursor++;
		else if (nc->menu_bud && nc->cursor < NB_PRESET_BUD - 1)
			nc->cursor++;
	}
	else if (ret == KEY_UP && nc->cursor > 0)
		nc->cursor--;
}

static int	ncurses_key_right(t_env *e, t_nc *nc)
{
	if (nc->menu_bud)
	{
		ncurses_parsing(e, nc);
		nc->menu = 1;
		return (0);
	}
	if (!nc->menu_bud)
		e->num = nc->cursor;
	if (e->num)
		nc->menu = 1;
	else
		nc->menu_bud = 1;
	if (e->num == NUM_TRI && GPU)
	{
		end_of_program(e, "[Make re] pour désactiver le mode GPU\n");
	}
	return (1);
}

static void	ncurses_key_left(t_env *e, t_nc *nc)
{
	(void)e;
	nc->menu = 0;
	nc->menu_bud = 0;
	nc->cursor = 0;
}

void		ncurses_key(t_env *e, t_nc *nc)
{
	int		ret;

	(void)e;
	timeout(1);
	ret = getch();
	if (ret > 'A' && ret < 'z')
		nc->key = ret;
	ncurses_key_move(e, nc, ret);
	if (ret == KEY_RIGHT)
	{
		if (!(ncurses_key_right(e, nc)))
			return ;
	}
	else if (ret == KEY_LEFT)
		ncurses_key_left(e, nc);
}
