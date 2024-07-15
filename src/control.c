/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:02:54 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 02:24:35 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

int	key_press(int keypress, t_data *data)
{
	printf("press %d\n", keypress);
	if (keypress == 100)
	{
		data->controls.left = true;
		if (data->hero.locomotion.state != FALL)
			character_change_state(&data->hero, RUN);
		data->hero.locomotion.dir = 2;
	}
	if (keypress == 97)
	{
		data->controls.right = true;
		if (data->hero.locomotion.state != FALL)
			character_change_state(&data->hero, RUN);
		data->hero.locomotion.dir = -2;
	}
	if (keypress == 65505)
	{
		data->hero.is_sprinting = true;
	}
	if (keypress == 117)
		data->hero.is_attacking = true;
	if (keypress == 65307)
		quit(data);
	if (keypress == 32)
	{
		if (data->hero.locomotion.state == FALL && data->hero.locomotion.double_jump < data->hero.locomotion.max_double_jump)
		{
			data->hero.locomotion.velocity_y += 5;
			data->hero.locomotion.double_jump++;
		}
		else if (data->hero.locomotion.state != FALL)
		{
			data->hero.locomotion.velocity_y = 10;
			add_position(&data->hero.locomotion, &data->hero.draw, 0, -50);
		}
	}
	return (0);
}

int	key_release(int key_release, t_data *data)
{
	// printf("release %d\n", keypress);
	if (key_release == 100)
	{
		data->controls.left = false;
		if (data->controls.right == false)
		{
			data->hero.locomotion.dir = 1;
			if (data->hero.locomotion.state != FALL)
				character_change_state(&data->hero, IDLE);
		}
		else
			data->hero.locomotion.dir = -2;
	}
	if (key_release == 97)
	{
		data->controls.right = false;
		if (data->controls.left == false)
		{
			data->hero.locomotion.dir = -1;
			if (data->hero.locomotion.state != FALL)
				character_change_state(&data->hero, IDLE);

		}
		else
			data->hero.locomotion.dir = 2;
	}
	if (key_release == 65505)
	{
		data->hero.is_sprinting = false;

	}
	if (key_release == 117)
		data->hero.is_attacking = false;
	return (0);
}

int	button_press(int button, int x, int y, t_data *data)
{
	(void)data;
	(void)x;
	(void)y;
	if (button == 1)
	{
		data->hero.is_attacking = true;
		character_change_state(&data->hero, data->hero.locomotion.state);
	}
	printf("button = %d\n", button);
	return (0);
}

int	button_release(int button, int x, int y, t_data *data)
{
	(void)data;
	(void)x;
	(void)y;
	if (button == 1)
	{
		data->hero.is_attacking = false;
		character_change_state(&data->hero, data->hero.locomotion.state);
	}
	printf("button = %d\n", button);
	return (0);
}