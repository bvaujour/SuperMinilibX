/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:54:50 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/18 00:38:05 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


static void	null_flipbook(t_flipbook *flipbook)
{
	int	i;

	i = 0;
	while (i < flipbook->nb_img)
	{
		flipbook->img[i].img_ptr = NULL;
		i++;
	}
}
static void	init_img_ptr(t_data *data)
{
	data->img_db.background.img_ptr = NULL;
	data->img_db.door.img_ptr = NULL;
	data->img_db.contour.img_ptr = NULL;
	data->img_db.saved_background.img_ptr = NULL;
	data->img_db.waves_fix.img_ptr = NULL;
	data->img_db.tile_Bas.img_ptr = NULL;
	data->img_db.tile_Haut.img_ptr = NULL;
	data->img_db.tile_Milieu.img_ptr = NULL;
	data->img_db.tile_HautD.img_ptr = NULL;
	data->img_db.tile_HautG.img_ptr = NULL;
	null_flipbook(&data->img_db.fire_bullet);
	null_flipbook(&data->img_db.fire_muzzle);
	null_flipbook(&data->img_db.hero_idle);
	null_flipbook(&data->img_db.hero_run);
	null_flipbook(&data->img_db.hero_jump);
	null_flipbook(&data->img_db.hero_shoot);
	null_flipbook(&data->img_db.hero_runshoot);
	null_flipbook(&data->img_db.hero_runshoot);
	null_flipbook(&data->img_db.waves);
	// null_flipbook(&data->img_db.hero_death);
}
void	init_draw(t_draw *draw, t_flipbook *flipbook, t_coor pos, char *name)
{
	draw->active_flipbook = flipbook;
	draw->counter = 0;
	draw->frame = &flipbook->img[0];
	draw->last_frame = &flipbook->img[0];
	draw->last_pos = pos;
	draw->pos = pos;
	draw->need_redraw = false;
	draw->dir = 1;
	draw->name = name;
	draw->rendered_last_frame = false;
}

t_img	ft_new_img(t_data *data, char *path)
{
	t_img	new;

	ft_init_img_clean(&new);
	new.img_ptr = mlx_xpm_file_to_image(data->engine.mlx_ptr, path,
			&new.width, &new.height);
	if (!new.img_ptr)
		quit_error(data, "ft_new_img: mlx_xpm_file_to_image");
	new.addr = (int *)mlx_get_data_addr(new.img_ptr,
			&new.bits_per_pixel, &new.line_length, &new.endian);
	return (new);
}
static void	init_mallocs(t_data *data)
{
	data->img_db.hero_idle.img = malloc(sizeof(t_img) * 10);
	if (!data->img_db.hero_idle.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.hero_jump.img = malloc(sizeof(t_img) * 10);
	if (!data->img_db.hero_jump.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.hero_run.img = malloc(sizeof(t_img) * 8);
	if (!data->img_db.hero_run.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.hero_shoot.img = malloc(sizeof(t_img) * 4);
	if (!data->img_db.hero_shoot.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.fire_muzzle.img = malloc(sizeof(t_img) * 5);
	if (!data->img_db.fire_muzzle.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.fire_bullet.img = malloc(sizeof(t_img) * 5);
	if (!data->img_db.fire_bullet.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.hero_runshoot.img = malloc(sizeof(t_img) * 8);
	if (!data->img_db.hero_runshoot.img)
		quit_error(data, "init_mallocs: Malloc");
	data->img_db.waves.img = malloc(sizeof(t_img) * 4);
	if (!data->img_db.hero_runshoot.img)
		quit_error(data, "init_mallocs: Malloc");
}

static void init_ptr(t_data *data)
{
	// a malloquer
	data->world.map = NULL;
	data->img_db.hero_idle.img = NULL;
	data->img_db.hero_run.img = NULL;
	// data->img_db.hero_death.img = NULL;
	data->img_db.hero_shoot.img = NULL;
	data->img_db.hero_runshoot.img = NULL;
	data->img_db.waves.img = NULL;
	data->world.animated_tiles = NULL;
	data->img_db.fire_bullet.img = NULL;
	data->img_db.fire_muzzle.img = NULL;
	data->paths.next_path = NULL;
	data->paths.path = NULL;
	data->paths.tile_b = NULL;
	data->paths.tile_h = NULL;
	data->paths.tile_hd = NULL;
	data->paths.tile_hg = NULL;
	data->paths.tile_m = NULL;
	data->paths.door = NULL;
	data->paths.background = NULL;
	data->paths.sky = NULL;
	data->paths.ground = NULL;

	// les img_ptr

	

}

void	init_values(t_data *data)
{
	data->stock = 200;
	data->hero.locomotion.state = IDLE;
	data->hero.locomotion.pos.x = 0;
	data->hero.locomotion.pos.y = 0;
	data->hero.locomotion.root.x = 100;
	data->hero.locomotion.root.y = 100;
	data->hero.locomotion.dir	= 1;
	data->hero.locomotion.ms = 3;
	data->hero.locomotion.double_jump = 0;
	data->hero.locomotion.max_double_jump = 2;
	data->hero.locomotion.velocity_y = -9.81;
	data->hero.locomotion.bounce = 0;
	data->hero.locomotion.gravity_scale = 0.5;
	data->hero.is_attacking = false;
	data->hero.is_sprinting = false;
	data->hero.is_sprinting = false;
	data->hero.weapon.last_attack = 0;
	data->hero.weapon.att_sec = 6;
	data->hero.speed_scale = 1;
	data->world.camera.x = 0;
	data->world.camera.y = 0;
	data->world.line_count = 0;
	data->world.line_len = 0;
	data->controls.right = false;
	data->controls.left = false;
	
}

static void	init_img(t_data *data)
{
	data->img_db.hero_idle.img[0] = ft_new_img(data, "textures/robotfree/xpm/Idle (2).xpm");
	data->img_db.hero_idle.img[1] = ft_new_img(data, "textures/robotfree/xpm/Idle (2).xpm");
	data->img_db.hero_idle.img[2] = ft_new_img(data, "textures/robotfree/xpm/Idle (3).xpm");
	data->img_db.hero_idle.img[3] = ft_new_img(data, "textures/robotfree/xpm/Idle (4).xpm");
	data->img_db.hero_idle.img[4] = ft_new_img(data, "textures/robotfree/xpm/Idle (5).xpm");
	data->img_db.hero_idle.img[5] = ft_new_img(data, "textures/robotfree/xpm/Idle (6).xpm");
	data->img_db.hero_idle.img[6] = ft_new_img(data, "textures/robotfree/xpm/Idle (7).xpm");
	data->img_db.hero_idle.img[7] = ft_new_img(data, "textures/robotfree/xpm/Idle (8).xpm");
	data->img_db.hero_idle.img[8] = ft_new_img(data, "textures/robotfree/xpm/Idle (9).xpm");
	data->img_db.hero_idle.img[9] = ft_new_img(data, "textures/robotfree/xpm/Idle (10).xpm");
	data->img_db.hero_jump.img[0] = ft_new_img(data, "textures/robotfree/xpm/Jump (1).xpm");
	data->img_db.hero_jump.img[1] = ft_new_img(data, "textures/robotfree/xpm/Jump (2).xpm");
	data->img_db.hero_jump.img[2] = ft_new_img(data, "textures/robotfree/xpm/Jump (3).xpm");
	data->img_db.hero_jump.img[3] = ft_new_img(data, "textures/robotfree/xpm/Jump (4).xpm");
	data->img_db.hero_jump.img[4] = ft_new_img(data, "textures/robotfree/xpm/Jump (5).xpm");
	data->img_db.hero_jump.img[5] = ft_new_img(data, "textures/robotfree/xpm/Jump (6).xpm");
	data->img_db.hero_jump.img[6] = ft_new_img(data, "textures/robotfree/xpm/Jump (7).xpm");
	data->img_db.hero_jump.img[7] = ft_new_img(data, "textures/robotfree/xpm/Jump (8).xpm");
	data->img_db.hero_jump.img[8] = ft_new_img(data, "textures/robotfree/xpm/Jump (9).xpm");
	data->img_db.hero_jump.img[9] = ft_new_img(data, "textures/robotfree/xpm/Jump (10).xpm");
	data->img_db.hero_runshoot.img[0] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (1).xpm");
	data->img_db.hero_runshoot.img[1] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (2).xpm");
	data->img_db.hero_runshoot.img[2] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (3).xpm");
	data->img_db.hero_runshoot.img[3] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (4).xpm");
	data->img_db.hero_runshoot.img[4] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (5).xpm");
	data->img_db.hero_runshoot.img[5] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (6).xpm");
	data->img_db.hero_runshoot.img[6] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (7).xpm");
	data->img_db.hero_runshoot.img[7] = ft_new_img(data, "textures/robotfree/xpm/RunShoot (8).xpm");
	data->img_db.hero_run.img[0] = ft_new_img(data, "textures/robotfree/xpm/Run (1).xpm");
	data->img_db.hero_run.img[1] = ft_new_img(data, "textures/robotfree/xpm/Run (2).xpm");
	data->img_db.hero_run.img[2] = ft_new_img(data, "textures/robotfree/xpm/Run (3).xpm");
	data->img_db.hero_run.img[3] = ft_new_img(data, "textures/robotfree/xpm/Run (4).xpm");
	data->img_db.hero_run.img[4] = ft_new_img(data, "textures/robotfree/xpm/Run (5).xpm");
	data->img_db.hero_run.img[5] = ft_new_img(data, "textures/robotfree/xpm/Run (6).xpm");
	data->img_db.hero_run.img[6] = ft_new_img(data, "textures/robotfree/xpm/Run (7).xpm");
	data->img_db.hero_run.img[7] = ft_new_img(data, "textures/robotfree/xpm/Run (8).xpm");

	data->img_db.hero_shoot.img[0] = ft_new_img(data, "textures/robotfree/xpm/Shoot (1).xpm");
	data->img_db.hero_shoot.img[1] = ft_new_img(data, "textures/robotfree/xpm/Shoot (2).xpm");
	data->img_db.hero_shoot.img[2] = ft_new_img(data, "textures/robotfree/xpm/Shoot (3).xpm");
	data->img_db.hero_shoot.img[3] = ft_new_img(data, "textures/robotfree/xpm/Shoot (4).xpm");

	data->img_db.fire_bullet.img[0] = ft_new_img(data, "textures/Bullet/Bullet_000.xpm");
	data->img_db.fire_bullet.img[1] = ft_new_img(data, "textures/Bullet/Bullet_001.xpm");
	data->img_db.fire_bullet.img[2] = ft_new_img(data, "textures/Bullet/Bullet_002.xpm");
	data->img_db.fire_bullet.img[3] = ft_new_img(data, "textures/Bullet/Bullet_003.xpm");
	data->img_db.fire_bullet.img[4] = ft_new_img(data, "textures/Bullet/Bullet_004.xpm");

	data->img_db.fire_muzzle.img[0] = ft_new_img(data, "textures/Bullet/Muzzle_000.xpm");
	data->img_db.fire_muzzle.img[1] = ft_new_img(data, "textures/Bullet/Muzzle_001.xpm");
	data->img_db.fire_muzzle.img[2] = ft_new_img(data, "textures/Bullet/Muzzle_002.xpm");
	data->img_db.fire_muzzle.img[3] = ft_new_img(data, "textures/Bullet/Muzzle_003.xpm");
	data->img_db.fire_muzzle.img[4] = ft_new_img(data, "textures/Bullet/Muzzle_004.xpm");

	data->img_db.waves.img[0] = ft_new_img(data, "textures/Tiles/waves0.xpm");
	data->img_db.waves.img[1] = ft_new_img(data, "textures/Tiles/waves1.xpm");
	data->img_db.waves.img[2] = ft_new_img(data, "textures/Tiles/waves2.xpm");
	data->img_db.waves.img[3] = ft_new_img(data, "textures/Tiles/waves3.xpm");
	data->img_db.waves_fix = ft_new_img(data, "textures/Tiles/waves_fix.xpm");
	
	data->img_db.contour = ft_new_img(data, "textures/HUD/countour.xpm");


	data->hero.idle = &data->img_db.hero_idle;
	data->hero.run = &data->img_db.hero_run;
	// data->hero.death = &data->img_db.hero_death;
	data->hero.jump = &data->img_db.hero_jump;
	data->hero.shoot = &data->img_db.hero_shoot;
	data->hero.runshoot = &data->img_db.hero_runshoot;
	init_draw(&data->hero.draw, &data->img_db.hero_idle, (t_coor){0, 0}, "hero");
}


void	init_bullets(t_data *data)
{
	int	i;
	int	max;

	i = 0;
	max = data->stock;
	while (i < max)
	{
		data->bullets[i].active = false;
		data->bullets[i].last_render = 0;
		data->bullets[i].locomotion.state = RUN;
		data->muzzles[i].repeat = 1;
		data->muzzles[i].active = false;
		init_draw(&data->bullets[i].draw, &data->img_db.fire_bullet, (t_coor){0, 0}, "bullet");
		init_draw(&data->muzzles[i].draw, &data->img_db.fire_muzzle, (t_coor){0, 0}, "muzzle");
		i++;
	}
}

static void	init_imgs_values(t_data *data)
{
	//NOMBRE IMAGE
	data->img_db.hero_idle.nb_img = 10;
	data->img_db.hero_jump.nb_img = 10;
	data->img_db.hero_run.nb_img = 8;
	data->img_db.hero_shoot.nb_img = 4;
	data->img_db.hero_runshoot.nb_img = 8;
	data->img_db.fire_bullet.nb_img = 5;
	data->img_db.fire_muzzle.nb_img = 5;
	data->img_db.waves.nb_img = 4;

	//IMG/SEC
	data->img_db.hero_idle.img_per_sec = 6;
	data->img_db.hero_runshoot.img_per_sec = 10;
	data->img_db.hero_jump.img_per_sec = 6;
	data->img_db.hero_run.img_per_sec = 10;
	data->img_db.hero_shoot.img_per_sec = 15;
	data->img_db.fire_bullet.img_per_sec = 10;
	data->img_db.fire_muzzle.img_per_sec = 18;
	data->img_db.waves.img_per_sec = 5;

}

static void	init_weapon(t_data *data, t_character *character, char *name)
{
	character->weapon.bullet_locomotion.pos.x = 0;
	character->weapon.bullet_locomotion.pos.y = 0;
	character->weapon.bullet_locomotion.velocity_y = 0;
	character->weapon.bullet_locomotion.bounce = 18;
	character->weapon.bullet_locomotion.ms = 10;
	character->weapon.bullet_locomotion.dir = 0;
	character->weapon.bullet_locomotion.gravity_scale = 0;
	character->weapon.bullet_dmg = 10;
	character->weapon.bullet_flipbook = &data->img_db.fire_bullet;
	character->weapon.muzzle_flipbook = &data->img_db.fire_muzzle;
	character->weapon.name = name;
}


void	init(t_data *data)
{
	init_ptr(data);
	init_mallocs(data);
	init_imgs_values(data);
	init_img_ptr(data);
	init_img(data);
	init_values(data);
	init_bullets(data);
	init_weapon(data, &data->hero, "bullet_hero");
}