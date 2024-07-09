/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_img_xpm_scaled.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:31 by bvaujour          #+#    #+#             */
/*   Updated: 2024/03/26 12:55:15 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

t_img	ft_new_img_xpm_scaled(t_mlx *mlx, int width, int height, char *path)
{
	t_img	new;
	t_img	to_feet;

	ft_init_img_clean(&new);
	new.img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
	new.addr = (int *)mlx_get_data_addr(new.img_ptr, &new.bits_per_pixel,
			&new.line_length, &new.endian);
	new.width = width;
	new.height = height;
	ft_init_img_clean(&to_feet);
	to_feet.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&to_feet.width, &to_feet.height);
	to_feet.addr = (int *)mlx_get_data_addr(to_feet.img_ptr,
			&to_feet.bits_per_pixel, &to_feet.line_length, &to_feet.endian);
	ft_draw_img_to_img_scaled(&new, &to_feet);
	mlx_destroy_image(mlx->mlx_ptr, to_feet.img_ptr);
	return (new);
}
