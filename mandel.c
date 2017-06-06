#include "fractol.h"

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

