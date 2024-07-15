/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:00:09 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 13:47:06 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


static bool	set_next_dispo_bullet(t_character *character, t_bullet *bullets, int i)
{
	static int	last_bullet_index = 0;
	int			index;

	index = (last_bullet_index + i) % 100;
	if (bullets[index].active == false)
	{
		bullets[index].active = true;
		bullets[index].draw.active_flipbook = character->weapon.bullet_flipbook;
		bullets[index].draw.frame = &character->weapon.bullet_flipbook->img[0];
		bullets[index].draw.last_frame = &character->weapon.bullet_flipbook->img[0];
		bullets[index].locomotion = character->weapon.bullet_locomotion;
		bullets[index].dmg = character->weapon.bullet_dmg;
		bullets[index].draw.name = character->weapon.name;
		if (character->locomotion.dir > 0)
		{
			bullets[index].locomotion.pos.x = character->locomotion.pos.x + character->draw.frame->width;
			bullets[index].locomotion.dir = 2;
		}
		else
		{
			bullets[index].locomotion.pos.x = character->locomotion.pos.x;
			bullets[index].locomotion.dir = -2;
		}
		bullets[index].locomotion.pos.y = character->locomotion.pos.y + character->draw.frame->height / 2 - bullets[index].draw.frame->height / 2;
		bullets[index].draw.last_pos = bullets[index].locomotion.pos;
		bullets[index].draw.pos = bullets[index].locomotion.pos;
		last_bullet_index = index;
		return (true);
	}
	return (false);
}

static bool	set_next_dispo_muzzle(t_character *character, t_effect *muzzles, int i)
{
	static int	last_muzzle_index = 0;
	int			index;

	index = (last_muzzle_index + i) % 100;
	if (muzzles[index].active == false)
	{
		muzzles[index].active = true;
		muzzles[index].draw.active_flipbook = character->weapon.muzzle_flipbook;
		muzzles[index].draw.frame = &character->weapon.muzzle_flipbook->img[0];
		muzzles[index].draw.last_frame = &character->weapon.muzzle_flipbook->img[0];
		if (character->locomotion.dir > 0)
			muzzles[index].draw.pos.x = character->locomotion.pos.x + character->draw.frame->width;
		else
			muzzles[index].draw.pos.x = character->locomotion.pos.x;

		muzzles[index].draw.pos.y = character->locomotion.pos.y + character->draw.frame->height / 2 - muzzles[index].draw.frame->height / 2;
		
		muzzles[index].draw.last_pos = muzzles[index].draw.pos;
		last_muzzle_index = index;
		return (true);
	}
	return (false);
}
void	character_fire(t_character *character, t_bullet *bullets, t_effect *muzzles)
{
	int			i;
	bool		bullet_found;
	bool		muzzle_found;

	if (gettime() - character->weapon.last_attack < 1000 / character->weapon.att_sec)
		return ;
	i = 0;
	bullet_found = false;
	muzzle_found = false;
	while (i < 100 && (!bullet_found || !muzzle_found))
	{
		if (!muzzle_found)
			muzzle_found = set_next_dispo_muzzle(character, muzzles, i);
		if (!bullet_found)
			bullet_found = set_next_dispo_bullet(character, bullets, i);
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