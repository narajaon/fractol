#include "fractol.h"

int		error_msg(int error)
{
	if (error == 1)
		ft_putstr_fd("Usage : ./fractol <value>\n1- Mandelbrot\
				\n2- Julia\n3- Burning Ship\
				\n4- README\n", 2);
	else if (error == 2)
		ft_putstr_fd("Couldn't allocate memory :(\n", 2);
	else if (error == 3)
		ft_putstr_fd("Invalid fractal :(\n", 2);
	else if (error == 4)
		ft_putstr_fd("Valid actions :\
				\n'c' to change colours\n'r' to reset the fractal\
				\nscroll w/ mousewheel to zoom in\n", 1);
	else
		ft_putstr_fd("Window closed, cya\n", 1);
	return (error);
}

int		change_col(int col)
{
	static int		i;
	int				tab[3];

	tab[0] = 0x0000FF00;
	tab[1] = 0x000174DF;
	tab[2] = 0x000000FF;
	i %= 3;
	return (tab[i++]);
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
			if (e->fract == 1)
				check_mandel(&e->pix, e);
			else if (e->fract == 2)
				check_julia(&e->pix, e);
			e->pix.y++;
		}
		e->pix.x++;
	}
}
