/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:50:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/31 18:00:24 by narajaon         ###   ########.fr       */
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
}

void	check_pix(t_pix *pix, t_env *e)
{
	int		c_r;
	int		c_i;
	int		tmp;

	c_r = pix->x;
	c_i = pix->y * WIN_X;
	init_struct(pix);
	while (pix->z_r * pix->z_r + pix->z_i * pix->z_i < 4 && pix->im < MAX_ITER)
	{
		tmp = pix->z_r;
		pix->z_r = pix->z_r * pix->z_r - pix->z_i * pix->z_i + c_r;
		pix->z_i = 2 * pix->z_i * tmp + c_i;
		pix->im++;
	}
	if (pix->im == MAX_ITER)
		e->img.img[c_r + c_i] = pix->col;
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
