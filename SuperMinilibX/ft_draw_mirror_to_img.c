/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_mirror_to_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:48:29 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/17 17:21:45 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

void	ft_draw_mirror_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;
	int	tmp_x;

	j = 0;
	while (j < src->height)
	{
		i = src->width - 1;
		tmp_x = x;
		while (i >= 0)
		{
			if (tmp_x + i >= 0 && y + j >= 0 && tmp_x + i < dst->width
				&& y + j < dst->height)
			{
				ft_set_image_pixel(dst, tmp_x, y + j, ft_get_pixel_img(src, i, j));
			}
			tmp_x++;
			i--;
		}
		j++;
	}
}