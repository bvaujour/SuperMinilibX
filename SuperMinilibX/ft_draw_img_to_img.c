/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_img_to_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:20:05 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/11 16:58:35 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

void	ft_draw_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < src->height)
	{
		i = 0;
		while (i < src->width)
		{
			if (x + i > 0 && y + j > 0 && x + i < dst->width
				&& y + j < dst->height)
			{
				ft_set_image_pixel(dst, x + i, y + j, ft_get_pixel_img(src, i, j));
			}
			i++;
		}
		j++;
	}
}