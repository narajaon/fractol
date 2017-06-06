/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/05 19:15:07 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook(int keycode, t_env *e)
{
	printf("key nb %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(e->mlx, e->img.img_ptr);
		mlx_destroy_window(e->mlx, e->win);
		exit(error_msg(0));
	}
	if (keycode == 15)
	{
		(e->fract == 1) ? init_mandel(e) : 0;
		(e->fract == 2) ? init_julia(e) : 0;
		print_fract(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	if (keycode == 8)
	{
		e->pix.col = change_col(e->pix.col);
		print_fract(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	if ((keycode == 126 || keycode == 125) && e->fract == 2)
	{
		e->i_jul *= (keycode == 126) ? 1.03 : 0.97;
		print_fract(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	return (keycode);
}

int		mouse_hook(int boutton, int x, int y, t_env *e)
{
	double		mouse_x;
	double		mouse_y;

	printf("mouse boutton %d x %d y %d\n", boutton, x, y);
	mouse_x = x * ((e->pix.x2 - e->pix.x1) / WIN_X) + e->pix.x1;
	mouse_y = y * ((e->pix.y2 - e->pix.y1) / WIN_Y) + e->pix.y1;
	printf("x %f y %f\n", mouse_x, mouse_y);
	if (boutton == 6)
	{
		(e->zoom < 1964714736118) ? zoom_fract(e, mouse_x, mouse_y) : 0;
		print_fract(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		exit(error_msg(1));
	e.fract = ft_atoi(av[1]);
	if (e.fract == 4)
		exit(error_msg(4));
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "Displaying Fract'ol");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr,
			&e.img.bpp, &e.img.size_line, &e.img.endian);
	if (e.fract == 1)
		do_mandel(&e);
	else if (e.fract == 2)
		do_julia(&e);
	return (0);
}
