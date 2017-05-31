/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 14:20:30 by narajaon          #+#    #+#             */
/*   Updated: 2017/05/31 16:59:07 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
//# include <mlx.h>
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include "./libft/libft.h"
# include <stdio.h>

# define MAX_ITER 50
# define WIN_X 1500
# define WIN_Y 1000

typedef struct s_pix
{
	int		x;
	int		y;
	int		c;
	int		z_r;
	int		z_i;
	int		im;
	int		col;
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
	void	*mlx;
	void	*win;
	void	*key;
	t_img	img;
	int		zoom;
}				t_env;

#endif
