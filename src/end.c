/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:01:35 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/18 00:39:20 by bvaujour         ###   ########.fr       */
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

void	free_reusable_data(t_data *data)
{
	if (data->img_db.background.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.background.img_ptr);
	data->img_db.background.img_ptr = NULL;
	if (data->img_db.saved_background.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.saved_background.img_ptr);
	data->img_db.saved_background.img_ptr = NULL;
	if (data->img_db.door.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.door.img_ptr);
	data->img_db.door.img_ptr = NULL;
	if (data->img_db.tile_Bas.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Bas.img_ptr);
	data->img_db.tile_Bas.img_ptr = NULL;
	if (data->img_db.tile_Haut.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Haut.img_ptr);
	data->img_db.tile_Haut.img_ptr = NULL;
	if (data->img_db.tile_HautD.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_HautD.img_ptr);
	data->img_db.tile_HautD.img_ptr = NULL;
	if (data->img_db.tile_HautG.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_HautG.img_ptr);
	data->img_db.tile_HautG.img_ptr = NULL;
	if (data->img_db.tile_Milieu.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.tile_Milieu.img_ptr);
	data->img_db.tile_Milieu.img_ptr = NULL;
	free(data->paths.path);
	data->paths.path = NULL;
	free(data->paths.door);
	data->paths.door = NULL;
	free(data->paths.tile_b);
	data->paths.tile_b = NULL;
	free(data->paths.tile_h);
	data->paths.tile_h = NULL;
	free(data->paths.tile_m);
	data->paths.tile_m = NULL;
	free(data->paths.tile_hd);
	data->paths.tile_hd = NULL;
	free(data->paths.tile_hg);
	data->paths.tile_hg = NULL;
	free(data->paths.background);
	data->paths.background = NULL;
	free(data->paths.sky);
	data->paths.sky = NULL;
	free(data->paths.ground);
	data->paths.ground = NULL;
	free(data->world.animated_tiles);
	data->world.animated_tiles = NULL;
	ft_freetab((void **)data->world.map);
	data->world.map = NULL;
}
void	quit(t_data *data)
{
	ft_del_img(data);
	free_reusable_data(data);
	free(data->paths.next_path);
	if (data->img_db.contour.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.contour.img_ptr);
	if (data->img_db.waves_fix.img_ptr)
		mlx_destroy_image(data->engine.mlx_ptr, data->img_db.waves_fix.img_ptr);
	mlx_do_key_autorepeaton(data->engine.mlx_ptr);
	if (data->engine.mlx_win)
		mlx_destroy_window(data->engine.mlx_ptr, data->engine.mlx_win);
	if (data->engine.mlx_ptr)
		mlx_destroy_display(data->engine.mlx_ptr);
	
	free(data->engine.mlx_ptr);
	free(data->img_db.hero_idle.img);
	free(data->img_db.waves.img);
	free(data->img_db.hero_jump.img);
	free(data->img_db.hero_run.img);
	free(data->img_db.hero_runshoot.img);
	free(data->img_db.hero_shoot.img);
	free(data->img_db.fire_muzzle.img);
	free(data->img_db.fire_bullet.img);
	exit(0);
}

void	quit_error(t_data *data, const char *str)
{
	ft_dprintf(2, "Error: \n");
	ft_dprintf(2, "%s\n", str);
	quit(data);
}