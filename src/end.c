/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:01:35 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 11:11:37 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

static void	ft_del_img(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (i < 10 && data->img_db.hero_idle.img && data->img_db.hero_idle.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.hero_idle.img[i].img_ptr);
		if (i < 8 && data->img_db.hero_runshoot.img && data->img_db.hero_runshoot.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.hero_runshoot.img[i].img_ptr);
		if (i < 10 && data->img_db.hero_jump.img && data->img_db.hero_jump.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.hero_jump.img[i].img_ptr);
		if (i < 8 && data->img_db.hero_run.img && data->img_db.hero_run.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.hero_run.img[i].img_ptr);
		if (i < 5 && data->img_db.fire_bullet.img && data->img_db.fire_bullet.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.fire_bullet.img[i].img_ptr);
		if (i < 5 && data->img_db.fire_muzzle.img && data->img_db.fire_muzzle.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.fire_muzzle.img[i].img_ptr);
		if (i < 4 && data->img_db.hero_shoot.img && data->img_db.hero_shoot.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.hero_shoot.img[i].img_ptr);
		if (i < 4 && data->img_db.waves.img && data->img_db.waves.img[i].img_ptr)
			mlx_destroy_image(data->engine.mlx_ptr, data->img_db.waves.img[i].img_ptr);
		i++;
	}
}

void	quit(t_data *data)
{
	ft_del_img(data);
	if (data->img_db.background.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.background.img_ptr);
	if (data->img_db.contour.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.contour.img_ptr);
	if (data->img_db.saved_background.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.saved_background.img_ptr);
	if (data->img_db.tile_Bas.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Bas.img_ptr);
	if (data->img_db.tile_Haut.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Haut.img_ptr);
	if (data->img_db.tile_HautD.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_HautD.img_ptr);
	if (data->img_db.tile_HautG.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_HautG.img_ptr);
	if (data->img_db.tile_Milieu.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Milieu.img_ptr);
	if (data->img_db.waves_fix.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.waves_fix.img_ptr);
	mlx_do_key_autorepeaton(data->engine.mlx_ptr);
	if (data->engine.mlx_win)
		mlx_destroy_window(data->engine.mlx_ptr, data->engine.mlx_win);
	if (data->engine.mlx_ptr)
		mlx_destroy_display(data->engine.mlx_ptr);

	free(data->engine.mlx_ptr);
	free(data->world.animated_tiles);
	free(data->img_db.hero_idle.img);
	free(data->img_db.waves.img);
	free(data->img_db.hero_jump.img);
	free(data->img_db.hero_run.img);
	free(data->img_db.hero_runshoot.img);
	free(data->img_db.hero_shoot.img);
	free(data->img_db.fire_muzzle.img);
	free(data->img_db.fire_bullet.img);
	ft_freetab((void **)data->world.map);
	exit(0);
}