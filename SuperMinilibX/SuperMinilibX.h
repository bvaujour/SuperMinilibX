/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMinilibX.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:34:06 by vanitas           #+#    #+#             */
/*   Updated: 2024/07/14 18:02:00 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPERMINILIBX_H
# define SUPERMINILIBX_H

# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>


typedef struct s_img
{
	void	*img_ptr;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			screen_w;
	int			screen_h;
}				t_mlx;


t_img	ft_new_img_xpm_scaled(t_mlx *engine, int width, int height, char *path);
t_img	ft_new_img_xpm(t_mlx *engine, char *path);
void	ft_draw_img_to_img_scaled(t_img *dst, t_img *src);
void	ft_draw_img_to_img(t_img *dst, t_img *src, int x, int y);
void	ft_draw_mirror_to_img(t_img *dst, t_img *src, int x, int y);
int		ft_get_pixel_img(t_img *img, int x, int y);
int		ft_set_image_pixel(t_img *image, int x, int y, int color);
void	ft_init_img_clean(t_img *img);
int		ft_power_on(t_mlx *engine, int width, int height);

#endif
