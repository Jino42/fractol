/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over_sampling_resize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:26:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/06/14 01:36:22 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	add_val(t_env *e, int y, int x, char *data)
{
	int y_s, x_s, i = 0, val = 0;
(void)e;
	y_s = 0;
	while (y_s < 3)
	{
		x_s = 0;
		while (x_s < 3)
		{
			val += data[(x + x_s) * OPP + (y + y_s) * (WIDTH_BUD * 4)];
			i++;
			x_s++;
		}
		y_s++;
	}
	return (val / i);
}

void		over_sampling_resize(t_env *e, char *tab)
{
	char	*new_data;
	new_data = ft_memalloc((MEM_OPENCL));
	(void)e;(void)new_data;
//	ft_printf("%i to %i\n", (MEM_OPENCL * 4), (MEM_OPENCL * 4) / 4);

	int y = 0, x, val;
	char	*data;
	int		nb = 3;

	data = tab;
	while (y < HEIGHT_BUD)
	{
		x = 0;
		while (x < WIDTH_BUD)
		{
			val = 0;
			val = add_val(e, y, x, data);
			new_data[(x / 4) * OPP + (y / 4) * (WIDTH * 4)] = val;
			new_data[(x / 4) * OPP + (y / 4) * (WIDTH * 4) + 1] = val;
			new_data[(x / 4) * OPP + (y / 4) * (WIDTH * 4) + 2] = val;
			x += nb;
		}
		y += nb;
	}
	mlxji_clear_img(e->img);
	ft_memcpy(e->img->data, new_data, (MEM_OPENCL));
	free(new_data);
}