
#include "fractol.hl"

#pragma OPENCL EXTENSION cl_khr_printf : enable
#pragma OPENCL EXTENSION cl_khr_double : enable

__kernel void	mandelbrot(
__global char *out,
t_tool tool,
int clock,
int	num,
float jul_y,
float jul_x)
{
	int		recup = get_global_id(0);
	if (recup < 0 || recup >= WIDTH * HEIGHT)
		return ;
	int		x = recup % WIDTH;
	int		y = recup / WIDTH;
	long int		d_x = x + (V_PRECI)tool.ajj_x + tool.move_x;
	long int		d_y = y + (V_PRECI)tool.ajj_y + tool.move_y;
	V_PRECI	c_r = 0;
	V_PRECI	c_i = 0;
	V_PRECI	z_r = 0;
	V_PRECI	z_i = 0;
	V_PRECI	tmp;
	int		i;
	t_px	px;
	float	h = clock;
	float	s = 0.7;
	float	v = 0.7;

	i = 0;
	if (num == 1)
	{
		c_r = (d_x) / (V_PRECI)tool.zoom + X1;
		c_i = (d_y) / (V_PRECI)tool.zoom + Y1;
		while (z_r * z_r + z_i * z_i < 4 && i < tool.iter)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			i++;
		}
	}
	else
	{
		z_r = (d_x) / (V_PRECI)tool.zoom + X1;
		z_i = (d_y) / (V_PRECI)tool.zoom + Y1;
		c_r = jul_x;
		c_i = jul_y;
		while (z_r * z_r + z_i * z_i < 4 && i < tool.iter)
		{
			tmp = z_r;
			z_r = z_r * z_r - z_i * z_i + c_r;
			z_i = 2 * z_i * tmp + c_i;
			i++;
		}
	}
	if (i != tool.iter)// && (i > 1)
	{
		h += (360 / (float)tool.iter) * i;
		if (h > 360)
		{
			h -= 360;
		}
		mlxji_hsv_to_rgb(&px, h, s, v);
		out[x * OPP + y * (WIDTH * 4)] = px.b;
		out[x * OPP + y * (WIDTH * 4) + 1] = px.g;
		out[x * OPP + y * (WIDTH * 4) + 2] = px.r;
	}
	else
	{
		out[x * OPP + y * (WIDTH * 4)] = 0;
		out[x * OPP + y * (WIDTH * 4) + 1] = 0;
		out[x * OPP + y * (WIDTH * 4) + 2] = 0;
	}
}
//		px.r = (255 / tool.iter) * i;
//		px.r = 0;
//		px.g = 0;
//		px.b = 0;
//		s = s + (0.30 / tool.iter) * i;
//		v = v + (0.10 / tool.iter) * i;
/*
HSV baic
g = 0;
b = 0;
*/
