/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pixel_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:19:39 by bvaujour          #+#    #+#             */
/*   Updated: 2024/03/26 11:31:42 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

int	ft_get_pixel_img(t_img *img, int x, int y)
{
	int	pixel_index;
	int	color;

	pixel_index = y * img->line_length / (img->bits_per_pixel / 8) + x;
	color = img->addr[pixel_index];
	return (color);
}