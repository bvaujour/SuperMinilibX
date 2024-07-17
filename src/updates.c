/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:23:58 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/17 20:56:24 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

static e_state	land(t_locomotion *locomotion, t_world *world, t_draw *draw)
{
	int		collided_tile_height;
	e_state	state;

	locomotion->double_jump = 0;
	if (locomotion->dir < -1 || locomotion->dir > 1)
		state = RUN;
	else
		state = IDLE;
	locomotion->velocity_y = -9.81;
	if (locomotion->bounce == 0)
	{
		collided_tile_height = (locomotion->root.y / world->tile_h) * world->tile_h;
		set_pos_y(locomotion, draw, collided_tile_height - draw->frame->height);
	}
	else
		locomotion->velocity_y += locomotion->bounce;
	return (state);
}

static e_state	gravity(t_locomotion *locomotion, t_world *world, t_draw *draw)
{
	locomotion->root.x = locomotion->pos.x + draw->frame->width / 2;
	locomotion->root.y = locomotion->pos.y + draw->frame->height;

	if (locomotion->velocity_y > 0 || locomotion->root.y < 0 || collision(world, locomotion->root) == AIR || collision(world, locomotion->root) == OUT)
	{
		add_position(locomotion, draw, 0, locomotion->velocity_y * -2);
		if (locomotion->velocity_y > -9.81)
			locomotion->velocity_y -= locomotion->gravity_scale;
		return (FALL);
	}
	else if (locomotion->state == FALL)
		return(land(locomotion, world, draw));
	return (locomotion->state);
}

bool	update_pose(t_draw *draw, int speed_scale)
{
	int	count;

	count = (gettime() / (1000 / (draw->active_flipbook->img_per_sec * speed_scale))) % draw->active_flipbook->nb_img;
	if (count != draw->counter)
	{
		draw->counter = count;
		draw->frame = &draw->active_flipbook->img[count];
		draw->need_redraw = true;
		return (true);
	}
	return (false);
}

static void	update_projectile(t_data *data, t_world *world, t_bullet *bullets)
{
	int 	i;
	bool	in_screen;
	int		max;
	
	i = -1;
	max = data->stock;
	while (++i < max)
	{
		if (bullets[i].active == true)
		{
			add_position(&bullets[i].locomotion, &bullets[i].draw, bullets[i].locomotion.ms * bullets[i].locomotion.dir, 0);
			bullets[i].draw.pos = bullets[i].locomotion.pos;
			bullets[i].draw.dir = bullets[i].locomotion.dir;
			in_screen = is_in_screen(&data->world, bullets[i].draw.frame, bullets[i].draw.pos);
			if (bullets[i].draw.dir < 0)
				bullets[i].locomotion.root.x = bullets[i].locomotion.pos.x;
			else	
				bullets[i].locomotion.root.x = bullets[i].locomotion.pos.x + bullets[i].draw.frame->width;
			bullets[i].locomotion.root.y = bullets[i].locomotion.pos.y + bullets[i].draw.frame->height/ 2;
			if (collision(&data->world, bullets[i].locomotion.root) != AIR || bullets[i].locomotion.pos.x > world->camera.x + world->screen_width + 500 || bullets[i].locomotion.pos.x < world->camera.x - 500 || bullets[i].locomotion.pos.x <= 0 || bullets[i].locomotion.pos.x >= data->world.map_width)
			{
				bullets[i].active = false;
				add_to_erase_list(data, &bullets[i].draw);
				continue ;
			}
			bullets[i].locomotion.state = gravity(&bullets[i].locomotion, world, &bullets[i].draw);
			update_pose(&bullets[i].draw, 1);
			if (gettime() - bullets[i].last_render < 10)
			{
				
				continue ;
			}
			// else
			// 	printf ("bullet not rendered \n");
			if (in_screen == true && bullets[i].draw.rendered_last_frame == false)
			{
				bullets[i].draw.rendered_last_frame = true;
				add_to_draw_list(data, &bullets[i].draw);
				bullets[i].last_render = gettime();
			}
			else if (in_screen == false && bullets[i].draw.rendered_last_frame == true)
			{
				add_to_erase_list(data, &bullets[i].draw);
				bullets[i].draw.rendered_last_frame = false;
			}
			else if (in_screen == true && bullets[i].draw.rendered_last_frame == true)
			{
				add_to_erase_list(data, &bullets[i].draw);
				add_to_draw_list(data, &bullets[i].draw);
				bullets[i].last_render = gettime();
			}
		}
	}
}

static void	update_tiles(t_data *data, t_animate_tile *tiles)
{
	int	i;
	bool	in_screen;
	bool	updated;

	i = 0;
	while (!tiles[i].end)
	{
		in_screen = is_in_screen(&data->world, tiles[i].draw.frame, tiles[i].draw.pos);
		updated	= update_pose(&tiles[i].draw, 1);

		if (in_screen == false)
		{
			// printf("tiles not rendered\n");
			tiles[i].draw.rendered_last_frame = false;
		}
		else if (tiles[i].draw.rendered_last_frame == false || updated)
		{
			tiles[i].draw.rendered_last_frame = true;
			add_to_erase_list(data, &tiles[i].draw);
			add_to_draw_list(data, &tiles[i].draw);
		}
		i++;
	}
}

static void	update_muzzles(t_data *data, t_effect *muzzles)
{
	int	i;
	bool	updated;
	int		max;

	i = 0;
	max = data->stock;
	while (i < max)
	{
		if (muzzles[i].active)
		{
			updated = update_pose(&muzzles[i].draw, 1);
			if (updated && muzzles[i].draw.counter == 0)
				muzzles[i].repeat--;
			if (updated && muzzles[i].repeat != -1)
			{
				add_to_erase_list(data, &muzzles[i].draw);
				add_to_draw_list(data, &muzzles[i].draw);
			}
			else if (updated && muzzles[i].repeat == -1)
			{
				add_to_erase_list(data, &muzzles[i].draw);
				muzzles[i].active = false;
				muzzles[i].repeat = 1;
			}
		}
		i++;
	}
}

static void	update_character(t_data *data, t_character *character)
{
	e_state	state;
	int		distance;

	state = gravity(&character->locomotion, &data->world, &character->draw);
	if (character->locomotion.dir < -1 || character->locomotion.dir > 1)
	{
		distance = character->locomotion.dir * character->locomotion.ms * character->speed_scale;
		character_move(character, &data->world, distance);
	}
	if (state != character->locomotion.state)
		character_change_state(character, state);
	if (state == RUN)
		update_pose(&character->draw, data->hero.speed_scale);
	else
		update_pose(&character->draw, 1);
}

void	update(t_data *data)
{
	int		distance;

	update_character(data, &data->hero);
	if (data->hero.locomotion.dir < -1 || data->hero.locomotion.dir > 1)
	{
		distance = data->hero.locomotion.dir * data->hero.locomotion.ms * data->hero.speed_scale;
		move_camera_x(data, distance);
	}
	data->world.camera.y = data->hero.locomotion.pos.y - data->world.screen_height / 2;
	if (data->world.camera.y > data->world.map_height - data->world.screen_height)
		data->world.camera.y = data->world.map_height - data->world.screen_height;
	if (data->world.camera.y < 0)
		data->world.camera.y = 0;
	update_muzzles(data, data->muzzles);
	update_tiles(data, data->world.animated_tiles);
	update_projectile(data, &data->world, data->bullets);
	if (data->hero.draw.need_redraw == true)
	{
		data->hero.draw.dir = data->hero.locomotion.dir;
		data->hero.draw.pos = data->hero.locomotion.pos;
		add_to_draw_list(data, &data->hero.draw);
		add_to_erase_list(data, &data->hero.draw);
	}
}