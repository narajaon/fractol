/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/04 17:02:53 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		error_msg(int error)
{
	if (error == 1)
	{
		ft_putstr_fd("Usage : ./fractol <value>\n1- Mandelbrot\
				\n2- Julia\n3- Burning Ship\n", 2);
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
	ft_putstr_fd("Window closed, cya\n", 1);
	return (0);
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
	return (keycode);
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
		e->img.img[e->pix.y * WIN_X + e->pix.x] = 0xFFFFFF;
	else
		e->img.img[e->pix.y * WIN_X + e->pix.x] = e->pix.col * e->pix.i * 255 / iter_max;
}

void	init_mandel(t_pix *pix, t_env *e)
{
	e->pix.im_x = (unsigned int)((e->pix.x2 - e->pix.x1) * e->zoom);
	e->pix.im_y = (unsigned int)((e->pix.y2 - e->pix.y1) * e->zoom);
}

void	zoom_mandel(t_env *e, int x, int y)
{
	double		cent_x;
	double		cent_y;

	cent_x = WIN_X / 2;
	cent_y = WIN_Y / 2;
	//printf("cent x %f cent y %f\n", cent_x, cent_y);
	e->pix.x1 *= e->pad;
	e->pix.x2 *= e->pad;
	e->pix.y1 *= e->pad;
	e->pix.y2 *= e->pad;
	e->pad_x *= 0.95;
	e->pad_y *= 0.95;
	/* x2 grandit quand il devient negatif!!! Meme chose pour y2 je suppose*/
	if (x > cent_x)
	{
		e->pix.x1 += e->pad_x;
		e->pix.x2 += e->pad_x;
	}
	else if (x < cent_x)
	{
		e->pix.x1 -= e->pad_x;
		e->pix.x2 -= e->pad_x;
	}
	if (y > cent_y)
	{
		e->pix.y1 += e->pad_y;
		e->pix.y2 += e->pad_y;
	}
	else if (y < cent_y)
	{
		e->pix.y1 -= e->pad_y;
		e->pix.y2 -= e->pad_y;
	}
	e->zoom *= 1.0526;
	printf("x1 %f x2 %f y1 %f y2 %f\n", e->pix.x1, e->pix.x2, e->pix.y1, e->pix.y2);
	//e->iter_max = 50 + e->iter_max % 15;
}

void	print_mandel2(t_env *e)
{
	init_mandel(&e->pix, e);
	e->pix.x = 0;
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

int		mouse_hook(int boutton, int x, int y, t_env *e)
{
	//printf("mouse boutton %d x %d y %d\n", boutton, x, y);
	if (boutton == 1)
	{
		//ft_bzero(e->img.img, sizeof(e->img.img));
		//ft_memset(e->img.img, 0x000000, WIN_X * WIN_Y);
		zoom_mandel(e, x, y);
		print_mandel2(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	}
	return (0);
}

int		do_mandel(t_env *e)
{
	e->iter_max = 150;
	e->h = 50;
	e->pix.col = 0x0000FF;
	e->pix.x = 0;
	e->pix.y = 0;
	e->pix.x1 = -2.1;
	e->pix.x2 = 0.6;
	e->pix.y1 = -1.2;
	e->pix.y2 = 1.2;
	e->zoom = 100;
	e->pad_x = fabs((e->pix.x2 - e->pix.x1) * 0.05);
	e->pad_y = fabs((e->pix.y2 - e->pix.y1) * 0.05);
	e->pad = 0.95;
	print_mandel2(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_key_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		exit(error_msg(1));
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIN_X, WIN_Y, "Displaying Fract'ol");
	e.img.img_ptr = mlx_new_image(e.mlx, WIN_X, WIN_Y);
	e.img.img = (int *)mlx_get_data_addr(e.img.img_ptr, &e.img.bpp, &e.img.size_line,
			&e.img.endian);
	//printf("bpp %d size %d endian %d\n", e.img.bpp, e.img.size_line, e.img.endian);
	do_mandel(&e);
	return (0);
}
