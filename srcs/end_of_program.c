/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:00:11 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/16 07:38:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	free_mlx(t_env *e, t_img *img)
{
	if (!e || !img)
		return ;
	if (e->mlx && e->img)
	mlx_destroy_image(e->mlx, e->img->img);
	if (e->mlx && e->win)
		mlx_destroy_window(e->mlx, e->win);
	if (e->img)
		free(e->img);
}

void		end_of_program(t_env *e)
{
	free_mlx(e, e->img);
	cl_end_opencl(e, &(e->cl));
	if (e->buff_patern)
		free(e->buff_patern);
	if (e->ftab)
		free(e->ftab);
}
