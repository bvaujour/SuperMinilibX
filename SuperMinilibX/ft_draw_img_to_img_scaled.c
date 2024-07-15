/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_img_to_img_scaled.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:20:34 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/11 13:46:05 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

static void	ft_cpy_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->line_length / 4) + x;
	image->addr[pixel] = color;
}

void	ft_draw_img_to_img_scaled(t_img *dst, t_img *src)
{
	int		i;
	int		j;
	float	x;
	float	y;

	i = 0;
	x = 0;
	while (i < dst->width)
	{
		j = 0;
		y = 0;
		while (j < dst->height)
		{
			ft_cpy_pixel(dst, i, j, ft_get_pixel_img(src, (int)x, (int)y));
			j++;
			y += (float)src->height / dst->height;
		}
		i++;
		x += (float)src->width / dst->width;
	}
}