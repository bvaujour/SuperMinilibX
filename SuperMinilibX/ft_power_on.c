/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_on.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:16:27 by bvaujour          #+#    #+#             */
/*   Updated: 2024/03/26 14:53:44 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

int	ft_power_on(t_mlx *mlx, int width, int height)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (dprintf(2, "ft_power_on: error mlx_init\n"), 1);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, width, height, "MLX_engine");
	if (!mlx->mlx_win)
		return (dprintf(2, "ft_power_on: error mlx_win\n"), 2);
	return (0);
}