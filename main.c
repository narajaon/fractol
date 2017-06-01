/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/01 19:35:02 by narajaon         ###   ########.fr       */
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

int		key_hook(int keycode, void *param)
{
	printf("key nb %d\n", keycode);
	if (keycode == 53)
		exit(error_msg(0));
	return (0);
}

int		mouse_hook(int boutton, int x, int y, void *param)
{
	printf("mouse boutton %d x %d y %d\n", boutton, x, y);
	return (0);
}

void	check_pix(t_pix *pix, t_env *e)
{
	double		tmp;
	int			iter_max;

	pix->c_r = pix->x / (double)(e->zoom) + pix->x1;
	pix->c_i = pix->y / (double)(e->zoom) + pix->y1;
	pix->z_r = 0;
	pix->z_i = 0;
	pix->i = 0;
	iter_max = e->iter_max;
	while (pix->z_r * pix->z_r + pix->z_i * pix->z_i < 4 && pix->i < iter_max)
	{
		tmp = pix->z_r;
		pix->z_r = pix->z_r * pix->z_r - pix->z_i * pix->z_i + pix->c_r;
		pix->z_i = 2 * pix->z_i * tmp + pix->c_i;
		++pix->i;
	}
	if (pix->i == iter_max)
		e->img.img[pix->x * WIN_X + pix->y] = 0xFFFFFF;
	else
		e->img.img[pix->x * WIN_X + pix->y] = pix->col * pix->i * 255 / iter_max;
}

void	init_mandel(t_pix *pix, t_env *e)
{
	pix->x1 = -2.1;
	pix->x2 = 0.6;
	pix->y1 = -1.2;
	pix->y2 = 1.2;
	pix->im_x = (unsigned int)((pix->x2 - pix->x1) * e->zoom);
	pix->im_y = (unsigned int)((pix->y2 - pix->y1) * e->zoom);
}

void	print_mandel2(t_pix *pix, t_env *e)
{
	init_mandel(pix, e);
	pix->x = 0;
	while (pix->x < pix->im_x)
	{
		pix->y = 0;
		while (pix->y < pix->im_y)
		{
			check_pix(pix, e);
			pix->y++;
		}
		pix->x++;
	}
}

int		do_mandel(t_env *e)
{
	t_pix	pix;
	int		i;
	int		key;

	i = 0;
	key = 0;
	e->zoom = 250;
	e->iter_max = 50;
	pix.col = 0x0000FF;
	pix.x = 0;
	pix.y = 0;
	print_mandel2(&pix, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img_ptr, 0, 0);
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
	printf("bpp %d size %d endian %d\n", e.img.bpp, e.img.size_line, e.img.endian);
	mlx_key_hook(e.win, &key_hook, e.key);
	mlx_mouse_hook(e.win, &mouse_hook, e.mouse);
	do_mandel(&e);
	mlx_loop(e.mlx);
	return (0);
}
