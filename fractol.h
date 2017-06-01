/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 14:20:30 by narajaon          #+#    #+#             */
/*   Updated: 2017/06/01 18:26:46 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
//# include <mlx.h>
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include "./libft/libft.h"
# include <stdio.h>

# define WIN_X 1000
# define WIN_Y 800

typedef struct s_pix
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	im_x;
	unsigned int	im_y;
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
	unsigned int		zoom;
	unsigned int		iter_max;
}				t_env;

#endif
