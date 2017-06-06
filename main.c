/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/06 10:18:23 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		error_msg(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Usage : ./fractol <value>\n1- Mandelbrot\
				\n2- Julia\n3- Burning Ship\
				\n4- README\n", 2);
		return (1);
	}
	if (error == 2)
	{
		ft_putstr_fd("Couldn't allocate memory :(\n", 2);
		return (2);
	}
	if (error == 3)
	{
		ft_putstr_fd("Invalid fractal :(\n", 2);
		return (3);
	}
	if (error == 4)
	{
		ft_putstr_fd("Valid actions :\
				\n'c' to change colours\n'r' to reset the fractal\
				\nUse the mousewheel to zoom in any direction\n", 1);
		return (4);
	}
	ft_putstr_fd("Window closed, cya\n", 1);
	return (0);
}

void	init_mandel(t_env *e)
{
	e->iter_max = 50;
	e->h = 50;
	e->pix.col = 0x0000FF;
	e->pix.x = 0;
	e->pix.y = 0;
	e->pix.x1 = -2.1;
	e->pix.x2 = 0.6;
	e->pix.y1 = -1.2;
	e->pix.y2 = 1.2;
	e->wid_x = 0;
	e->wid_y = 0;
	e->zoom = 100;
}

void	check_pix(t_pix *pix, t_env *e)
{
	double		tmp;
	int			iter_max;

	e->pix.c_r = e->pix.x / (double)(e->zoom) + e->pix.x1;
	e->pix.c_i = e->pix.y / (double)(e->zoom) + e->pix.y1;
	e->pix.z_r = 0;
	e->pix.z_i = 0;
	e->pix.i = 0;
	iter_max = e->iter_max;
	while (e->pix.z_r * e->pix.z_r + e->pix.z_i * e->pix.z_i < 4 && e->pix.i < iter_max)
	{
		tmp = e->pix.z_r;
		e->pix.z_r = e->pix.z_r * e->pix.z_r - e->pix.z_i * e->pix.z_i + e->pix.c_r;
		e->pix.z_i = 2 * e->pix.z_i * tmp + e->pix.c_i;
		++e->pix.i;
	}
	if (e->pix.i == iter_max)
		e->img.img[e->pix.y * WIN_X + e->pix.x] = 0x00FFFFFF;
	else
		e->img.img[e->pix.y * WIN_X + e->pix.x] = 
			(int)(e->pix.col * e->pix.i * e->pix.col / iter_max) & (0x00FFFFFF);
}

void	zoom_fract(t_env *e, double x, double y)
{
	e->wid_x = (e->pix.x2 - e->pix.x1) / 2;
	e->wid_y = (e->pix.y2 - e->pix.y1) / 2;
	e->pix.x1 = x - e->wid_x * 0.95;
	e->pix.x2 = x + e->wid_x * 0.95;
	e->pix.y1 = y - e->wid_y * 0.95;
	e->pix.y2 = y + e->wid_y * 0.95;
	e->zoom *= 1.05264;
	e->iter_max++;
}

void	print_fract(t_env *e)
{
	e->pix.x = 0;
	e->pix.im_x = (unsigned int)((e->pix.x2 - e->pix.x1) * e->zoom);
	e->pix.im_y = (unsigned int)((e->pix.y2 - e->pix.y1) * e->zoom);
	while (e->pix.x < e->pix.im_x)
	{
		e->pix.y = 0;
		while (e->pix.y < e->pix.im_y)
		{
			check_pix(&e->pix, e);
			e->pix.y++;
		}
		e->pix.x++;
	}
}

int		change_col(int col)
{
	static int		i;
	int				tab[3];

	tab[0] = 0x000000FF;
	tab[1] = 0x002EFE2E;
	tab[2] = 0x000174DF;
	i = (i + 1) % 3;
	return (tab[i]);
}

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
		init_mandel(e);
		print_fract(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	if (keycode == 8)
	{
		e->pix.col = change_col(e->pix.col);
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

int		do_mandel(t_env *e)
{
	init_mandel(e);
	printf("x1 %f x2 %f y1 %f y2 %f\n", e->pix.x1, e->pix.x2, e->pix.y1, e->pix.y2);
	print_fract(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	e;
	int		fract;

	if (ac < 2)
		exit(error_msg(1));
	fract = ft_atoi(av[1]);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "Displaying Fract'ol");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr,
			&e.img.bpp, &e.img.size_line, &e.img.endian);
	if (fract == 4)
		exit(error_msg(4));
	do_mandel(&e);
	//do_julia(&e);
	return (0);
}
