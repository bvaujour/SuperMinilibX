/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:00:09 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 02:22:21 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	character_fire(t_character *character, t_bullet *bullets)
{
	int	i;

	if (gettime() - character->weapon.last_attack < 1000 / character->weapon.att_sec)
		return ;
	i = 0;
	while (i < 100)
	{
		if (bullets[i].active == false)
		{
			bullets[i].active = true;
			bullets[i].draw.active_flipbook = character->weapon.bullet_flipbook;
			bullets[i].draw.frame = &character->weapon.bullet_flipbook->img[0];
			bullets[i].draw.last_frame = &character->weapon.bullet_flipbook->img[0];
			bullets[i].locomotion = character->weapon.bullet_locomotion;
			bullets[i].dmg = character->weapon.bullet_dmg;
			if (character->locomotion.dir > 0)
			{
				bullets[i].locomotion.pos.x = character->locomotion.pos.x + character->draw.frame->width;
				bullets[i].locomotion.dir = 2;
			}
			else
			{
				bullets[i].locomotion.pos.x = character->locomotion.pos.x;
				bullets[i].locomotion.dir = -2;
			}
			bullets[i].locomotion.pos.y = character->locomotion.pos.y + character->draw.frame->height / 2;
			bullets[i].draw.last_pos = bullets[i].locomotion.pos;
			bullets[i].draw.pos = bullets[i].locomotion.pos;
			break ;
		}
		i++;
	}
	character->weapon.last_attack = gettime();
}

void	character_change_state(t_character *character, e_state new_state)
{
	character->locomotion.state = new_state;
	switch (character->locomotion.state)
	{
		case IDLE:
			if (character->is_attacking)
				character->draw.active_flipbook = character->shoot;
			else
				character->draw.active_flipbook = character->idle;
			break ;
		case FALL:
			character->draw.active_flipbook = character->jump;
			break ;
		case RUN:
			if (character->is_attacking)
				character->draw.active_flipbook = character->runshoot;
			else
			character->draw.active_flipbook = character->run;
			break ;
		case DEAD:
			break ;
	}
	character->draw.counter = 0;
	character->draw.need_redraw = true;
}

void character_move(t_character *character, t_world *world, int distance)
{

	if (character->locomotion.dir >= -1 && character->locomotion.dir <= 1)
		return ;
	character->locomotion.root.x = character->locomotion.pos.x + character->draw.frame->width / 2;
	character->locomotion.root.y = character->locomotion.pos.y + character->draw.frame->height - 20;
	if (character->locomotion.pos.x + character->draw.frame->width + distance >= world->map_width || character->locomotion.pos.x + distance < 0)
		return ;
	if (character->locomotion.root.y >= 0 &&  character->locomotion.root.y < world->screen_height && world->map[character->locomotion.root.y / world->tile_h][(character->locomotion.root.x + distance) / world->tile_w] != '0')
		return ;
	add_position(&character->locomotion, &character->draw, distance, 0);
}

void	character_sprint(t_character *character, float acceleration)
{
	if (acceleration > 0 && character->speed_scale < 5)
		character->speed_scale += acceleration;
	else if (acceleration < 0 && character->speed_scale > 1)
		character->speed_scale += acceleration;
	if (character->speed_scale < 1)
		character->speed_scale = 1;
}