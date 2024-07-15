/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:23:58 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 03:47:12 by bvaujour         ###   ########.fr       */
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
	if (locomotion->root.y >= world->screen_height - 100)
		return (DEAD);
	if (locomotion->velocity_y > 0 || locomotion->root.y < 0 || locomotion->root.y >= world->screen_height - 100 || (locomotion->root.x > 0 && locomotion->root.x < world->map_width && world->map[locomotion->root.y / world->tile_h][locomotion->root.x / world->tile_w] == '0'))
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

int	update_pose(t_draw *draw, int speed_scale)
{
	int	count;

	count = (gettime() / (1000 / (draw->active_flipbook->img_per_sec * speed_scale))) % draw->active_flipbook->nb_img;
	if (count != draw->counter || draw->need_redraw == true)
	{
		draw->counter = count;
		draw->frame = &draw->active_flipbook->img[count];
		draw->need_redraw = true;
		return (1);
	}
	return (0);
}

static void	update_projectile(t_data *data, t_world *world, t_bullet *bullets)
{
	int i;

	i = -1;
	while (++i < 100)
	{
		if (bullets[i].active == true)
		{
			if (bullets[i].locomotion.pos.x > world->camera.x + world->screen_width + 500 || bullets[i].locomotion.pos.x < world->camera.x - 500)
			{
				bullets[i].active = false;
				add_to_erase_list(data, &bullets[i].draw);
				continue ;
			}
			bullets[i].locomotion.state = gravity(&bullets[i].locomotion, world, &bullets[i].draw);
			add_position(&bullets[i].locomotion, &bullets[i].draw, bullets[i].locomotion.ms * bullets[i].locomotion.dir, 0);
			update_pose(&bullets[i].draw, 1);
			bullets[i].draw.pos = bullets[i].locomotion.pos;
			bullets[i].draw.dir = bullets[i].locomotion.dir;
			add_to_draw_list(data, &bullets[i].draw);
			add_to_erase_list(data, &bullets[i].draw);
		}
	}
}

static void	update_tiles(t_data *data, t_animate_tile *tiles)
{
	int	i;

	i = 0;
	while (!tiles[i].end)
	{
		if (update_pose(&tiles[i].draw, 1))
		{
			add_to_draw_list(data, &tiles[i].draw);
			add_to_erase_list(data, &tiles[i].draw);
		}
		i++;
	}
}

void	update(t_data *data)
{
	e_state	state;
	int		distance;

	state = gravity(&data->hero.locomotion, &data->world, &data->hero.draw);
	if (state != data->hero.locomotion.state)
		character_change_state(&data->hero, state);
	update_projectile(data, &data->world, data->bullets);
	update_tiles(data, data->world.waves);
	if (data->hero.locomotion.dir < -1 || data->hero.locomotion.dir > 1)
	{
		distance = data->hero.locomotion.dir * data->hero.locomotion.ms * data->hero.speed_scale;
		character_move(&data->hero, &data->world, distance);
		move_camera_x(data, distance);
	}
	if (data->hero.locomotion.state == FALL)
		update_pose(&data->hero.draw, 1);
	else
		update_pose(&data->hero.draw, data->hero.speed_scale);
}