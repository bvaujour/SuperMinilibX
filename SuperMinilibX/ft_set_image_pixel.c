/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_image_pixel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:18:51 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/11 13:21:48 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

int	ft_set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	if (color == (int)0xFF000000)
	{
		return (0);
	}
	pixel = y * (image->line_length / 4) + x;
	image->addr[pixel] = color;
	return (1);
}
