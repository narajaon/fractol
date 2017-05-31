/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/31 19:39:27 by narajaon         ###   ########.fr       */
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

int		key_fun(int keycode, void *param)
{
	printf("key nb %d\n", keycode);
	if (keycode == 53)
		exit(error_msg(0));
	return (0);
}

void	init_struct(t_pix *pix)
{
	pix->c = 0;
	pix->z_r = 0;
	pix->z_i = 0;
	pix->im = 0;
	pix->zone_x[0] = -2.1;
	pix->zone_x[1] = 0.6;
	pix->zone_y[0] = -1.2;
	pix->zone_x[1] = 1.2;
}

void	get_col(t_pix *pix, t_env *e, int c[2])
{
	float	img[2];
	int		tmp;

	img[0] = (pix->zone_x[1] - pix->zone_x[0]) * e->zoom;
	img[1] = (pix->zone_y[1] - pix->zone_y[0]) * e->zoom;
	while (pix->z_r * pix->z_r + pix->z_i * pix->z_i < 4 && pix->im < MAX_ITER)
	{
		tmp = pix->z_r;
		pix->z_r = pix->z_r * pix->z_r - pix->z_i * pix->z_i + c[0];
		pix->z_i = 2 * pix->z_i * tmp + c[1];
		pix->im++;
	}
	if (pix->im == MAX_ITER)
		e->img.img[c[0] + c[1]] = pix->col;
}

void	check_pix(t_pix *pix, t_env *e)
{
	int		c[2];
	int		tmp;

	init_struct(pix);
	c[0] = pix->x / e->zoom + pix->zone_x[0];
	c[1] = (pix->y * WIN_X) / e->zoom + pix->zone_y[0];
	get_col(pix, e, c);
}

void	print_mandel(t_pix *pix, t_env *e)
{
	while (pix->y < WIN_Y)
	{
		pix->x = 0;
		while (pix->x < WIN_X)
		{
			//e->img.img[pix->y * WIN_X + pix->x] = pix->col;
			check_pix(pix, e);
			pix->x++;
		}
		pix->y++;
	}
}

int		do_mandel(t_env *e)
{
	t_pix	pix;
	int		i;

	i = 0;
	e->zoom = 100;
	pix.col = 0xFF00FF;
	pix.x = 0;
	pix.y = 0;
	print_mandel(&pix, e);
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
	mlx_key_hook(e.win, &key_fun, e.key);
	do_mandel(&e);
	mlx_loop(e.mlx);
	return (0);
}
