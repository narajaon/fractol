/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 14:20:30 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/05 18:59:09 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
//# include <mlx.h>
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include "./libft/libft.h"
# include <stdio.h>
# include <math.h>

# define WIN_X 270
# define WIN_Y 240

typedef struct s_pix
{
	unsigned int	x;
	unsigned int	y;
	double			im_x;
	double			im_y;
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			c_r;
	double			c_i;
	double			z_r;
	double			z_i;
	double			i;
	int				col;

}				t_pix;

typedef struct s_img
{
	void	*img_ptr;
	int		*img;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_env
{
	void				*mlx;
	void				*win;
	void				*key;
	void				*mouse;
	t_img				img;
	double				zoom;
	unsigned int		iter_max;
	t_pix				pix;
	double				h;
	double				w;
	double				pad_x;
	double				pad_y;
	double				pad;
	double				wid_x;
	double				wid_y;
}				t_env;

int		do_mandel(t_env *e);
int		mouse_hook(int boutton, int x, int y, t_env *e);
int		key_hook(int keycode, t_env *e);
void	zoom_fract(t_env *e, double x, double y);
int		change_col(int col);

#endif
