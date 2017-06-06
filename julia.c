/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:31:33 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/06 17:41:07 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_julia(t_env *e)
{
	e->iter_max = 50;
	e->pix.col = 0x0000FF;
	e->pix.x = 0;
	e->pix.y = 0;
	e->pix.x1 = -1.35;
	e->pix.x2 = 1.35;
	e->pix.y1 = -1.2;
	e->pix.y2 = 1.2;
	e->wid_x = 0;
	e->wid_y = 0;
	e->zoom = 100;
	e->i_jul = 1;
}

void	check_julia(t_env *e)
{
	double		tmp;
	double		c_r;
	double		c_i;
	int			iter_max;

	c_r = 0.285;
	c_i = 0.01;
	e->pix.c_r = c_r * e->i_jul;
	e->pix.c_i = c_i * e->i_jul;
	e->pix.z_r = e->pix.x / e->zoom + e->pix.x1;
	e->pix.z_i = e->pix.y / e->zoom + e->pix.y1;
	e->pix.i = 0;
	iter_max = e->iter_max;
	while (pow(e->pix.z_r, 2) + pow(e->pix.z_i, 2) < 4 && e->pix.i < iter_max)
	{
		tmp = e->pix.z_r;
		e->pix.z_r = pow(e->pix.z_r, 2) - pow(e->pix.z_i, 2) + e->pix.c_r;
		e->pix.z_i = 2 * e->pix.z_i * tmp + e->pix.c_i;
		++e->pix.i;
	}
	if (e->pix.i == iter_max)
		e->img.img[e->pix.y * WIN_X + e->pix.x] = 0x00FFFFFF;
	else
		e->img.img[e->pix.y * WIN_X + e->pix.x] =
			(int)(e->pix.col * e->pix.i * e->pix.col / iter_max) & (0x00FFFFFF);
}

int		do_julia(t_env *e)
{
	init_julia(e);
	print_fract(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
