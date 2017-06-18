/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 02:10:14 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/18 05:55:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void init_basic(t_env *e, t_tool *tool)
{
	tool->zoom = 300;
	tool->move_x = (WIDTH / 2 * -1) + ((2.1) * tool->zoom);
	tool->move_y = (HEIGHT / 2 * -1) + ((1.2) * tool->zoom);
	e->bud.over = 1;
}
/*
static void init_bud(t_env *e, t_tool *tool, t_bud *bud)
{
	int		set_zoom[5];

	set_zoom[0] = 0;
	set_zoom[1] = 300;
	set_zoom[2] = 700;
	set_zoom[3] = 1400;
	set_zoom[4] = 3000;
	e->width_bud = HEIGHT * e->varover[bud->over];
	e->height_bud = WIDTH * e->varover[bud->over];
	e->mem_opencl_bud = e->width_bud * e->height_bud;
	(void)tool;
	tool->move_y = (e->height_bud / 2 * -1) + ((1.2) * set_zoom[bud->over]);
	e->buff_patern = ft_memalloc(e->mem_opencl_bud * sizeof(int));
	e->ftab = ft_memalloc(e->mem_opencl_bud * 4);		
}*/

static void	init_env(t_env *e)
{
	e->varover[0] = 0;
	e->varover[1] = 1;
	e->varover[2] = 2;
	e->varover[3] = 4;
	e->varover[4] = 8;
	e->varover[5] = 16;
	e->tool.iter = 50;
	ft_strcpy(e->name_fractal[0], "buddhabrot");
	ft_strcpy(e->name_fractal[1], "mandelbrot");
	ft_strcpy(e->name_fractal[2], "julia");
	ft_strcpy(e->name_preset[0], "preset_bud/example3");
	ft_strcpy(e->name_preset[1], "preset_bud/example2");
	ft_strcpy(e->name_preset[2], "mandelbrot.cl");
	ft_strcpy(e->name_preset[3], "preset_bud/");
	ft_strcpy(e->name_preset[4], "");
}

static int get_arg(t_env *e, int argc, char **argv)
{
	(void)e;
	(void)argv;
	if (argc != 1)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_bzero(&e, sizeof(t_env));
	if (!(get_arg(&e, argc, argv)))
		return (0);
	init_env(&e);
//	ncurses_init(&e, &e.nc, NC_HEIGHT, NC_WIDTH);
//	while (!e.nc.menu)
//		ncurses_menu(&e, &e.nc);
//	if (e.num || !GPU)
		init_basic(&e, &e.tool);
//	else
//		init_bud(&e, &e.tool, &e.bud);
	init_mlx(&e);
//	if (GPU)
//		cl_init_opencl(&e);
	draw_tri(&e);
	mlx_hook(e.win, 2, 0, &event_key_on, &e);
	mlx_key_hook(e.win, &event_key_off, &e);
	mlx_mouse_hook(e.win, &event_mouse, &e);
	mlx_hook(e.win, 6, 0, &event_move_mouse, &e);
	mlx_loop_hook(e.mlx, &loop, &e);
	mlx_loop(e.mlx);
	end_of_program(&e, NULL);
//	ft_bzero(&e, sizeof(t_env));
//	while(1);
	return (0);
}
