/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:34:32 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/06 17:41:13 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_burning(t_env *e)
{
	e->iter_max = 50;
	e->pix.col = 0x0000FF;
	e->pix.x = 0;
	e->pix.y = 0;
	e->pix.x1 = -1.7;
	e->pix.x2 = 1;
	e->pix.y1 = -1.5;
	e->pix.y2 = 0.9;
	e->wid_x = 0;
	e->wid_y = 0;
	e->zoom = 100;
}

void	check_burning(t_env *e)
{
	double		tmp;
	int			iter_max;

	e->pix.c_r = e->pix.x / (double)(e->zoom) + e->pix.x1;
	e->pix.c_i = e->pix.y / (double)(e->zoom) + e->pix.y1;
	e->pix.z_r = 0;
	e->pix.z_i = 0;
	e->pix.i = 0;
	iter_max = e->iter_max;
	while (pow(e->pix.z_r, 2) + pow(e->pix.z_i, 2) < 4 && e->pix.i < iter_max)
	{
		tmp = e->pix.z_r;
		e->pix.z_r = pow(e->pix.z_r, 2) - pow(e->pix.z_i, 2) + e->pix.c_r;
		e->pix.z_i = 2 * fabs(e->pix.z_i) * fabs(tmp) + e->pix.c_i;
		++e->pix.i;
	}
	if (e->pix.i == iter_max)
		e->img.img[e->pix.y * WIN_X + e->pix.x] = 0x00FFFFFF;
	else
		e->img.img[e->pix.y * WIN_X + e->pix.x] =
			(int)(e->pix.col * e->pix.i * e->pix.col / iter_max) & (0x00FFFFFF);
}

int		do_burning(t_env *e)
{
	init_burning(e);
	print_fract(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}
