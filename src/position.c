/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:51:38 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/17 10:12:49 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	add_position(t_locomotion *locomotion, t_draw *draw, int delta_x, int delta_y)
{
	if (delta_x == 0 && delta_y == 0)
		return ;
	locomotion->pos.x += delta_x;
	locomotion->pos.y += delta_y;
	draw->need_redraw = true;
}

void	set_pos_x(t_locomotion *locomotion, t_draw *draw, int new_pos_x)
{
	if (locomotion->pos.x == new_pos_x)
		return ;
	locomotion->pos.x = new_pos_x;
	draw->need_redraw = true;

}
void	set_pos_y(t_locomotion *locomotion, t_draw *draw, int new_pos_y)
{
	if (locomotion->pos.y == new_pos_y)
		return ;
	locomotion->pos.y = new_pos_y;
	draw->need_redraw = true;
}

void	move_camera_x(t_data *data, int distance)
{
	int	centre_gauche;
	int	centre_droit;

	centre_gauche = data->engine.screen_w / 2 - 2 * data->hero.draw.frame->width;
	centre_droit = data->engine.screen_w / 2 + data->hero.draw.frame->width;
	if (data->hero.locomotion.dir < -1 && data->hero.locomotion.pos.x - data->world.camera.x < centre_gauche && data->world.camera.x + distance >= 0)
		data->world.camera.x += distance;
	else if (data->hero.locomotion.dir > 1 && data->hero.locomotion.pos.x - data->world.camera.x > centre_droit && data->world.camera.x + data->engine.screen_w + distance <= data->world.map_width)
		data->world.camera.x += distance;
}

