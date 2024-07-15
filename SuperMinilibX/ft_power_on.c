/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_on.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:16:27 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/11 16:14:23 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperMinilibX.h"

int	ft_power_on(t_mlx *engine, int width, int height)
{
	engine->mlx_ptr = mlx_init();
	if (!engine->mlx_ptr)
		return (dprintf(2, "ft_power_on: error engine_init\n"), 1);
	engine->screen_w = width;
	engine->screen_h = height;
	engine->mlx_win = mlx_new_window(engine->mlx_ptr, engine->screen_w, engine->screen_h, "engine_engine");
	if (!engine->mlx_win)
		return (dprintf(2, "ft_power_on: error engine_win\n"), 2);
	return (0);
}