/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_img_xpm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:21:41 by bvaujour          #+#    #+#             */
/*   Updated: 2024/03/26 13:33:14 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"


t_img	ft_new_img_xpm(t_mlx *mlx, char *path)
{
	t_img	new;

	ft_init_img_clean(&new);
	new.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&new.width, &new.height);
	new.addr = (int *)mlx_get_data_addr(new.img_ptr,
			&new.bits_per_pixel, &new.line_length, &new.endian);
	return (new);
}
