/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:43:45 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 03:39:11 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../lib/game.h"


static void	restore_background(t_img *background, t_img *saved_background, t_coor start, t_coor end)
{
	int	x;
	int	y;

	y = -1;
	while (start.y + ++y < end.y)
	{
		if (start.y + y >= background->height || start.y + y < 0)
			continue ;
		x = -1;
		while (start.x + ++x < end.x)
		{
			if (start.x + x >= background->width || start.x + x < 0)
				continue ;
			ft_set_image_pixel(background, start.x + x, start.y + y, ft_get_pixel_img(saved_background,  start.x + x, start.y + y));
		}
	}
}



static void	restore(t_draw **to_erase, int nb, t_img *background, t_img *saved_background)
{
	int	i;
	t_coor	draw_end;

	i = 0;

	while (i < nb)
	{
		draw_end.x = to_erase[i]->last_pos.x + to_erase[i]->last_frame->width;
		draw_end.y = to_erase[i]->last_pos.y + to_erase[i]->last_frame->height;
		restore_background(background, saved_background, to_erase[i]->last_pos, draw_end);
		i++;
	}
}

static void	redraw(t_draw **to_draw, int nb, t_img *background)
{
	int	i;


	i = 0;

	while (i < nb)
	{
		if (to_draw[i]->dir < 0)
			ft_draw_mirror_to_img(background, to_draw[i]->frame, to_draw[i]->pos.x, to_draw[i]->pos.y);
		else
			ft_draw_img_to_img(background, to_draw[i]->frame, to_draw[i]->pos.x, to_draw[i]->pos.y);
		to_draw[i]->need_redraw = false;
		to_draw[i]->last_frame = to_draw[i]->frame;
		to_draw[i]->last_pos = to_draw[i]->pos;
		i++;
	}
}

// static void	restore(t_data *data)
// {
// 	int	i;
// 	t_coor	draw_end;

// 	i = 0;
	
// 	while (i < 100)
// 	{
// 		if (data->bullets[i].draw.need_redraw)
// 		{
// 			draw_end.x = data->bullets[i].draw.last_pos.x + data->bullets[i].draw.last_frame->width;
// 			draw_end.y = data->bullets[i].draw.last_pos.y + data->bullets[i].draw.last_frame->height;
// 			restore_background(&data->img_db.background, &data->img_db.saved_background, data->bullets[i].draw.last_pos, draw_end);
// 		}
// 		i++;
// 	}
// 	printf("%d\n", i);
// 	i = 0;
// 	while (!data->world.waves[i].end)
// 	{
// 		if (data->world.waves[i].draw.need_redraw)
// 		{
// 			draw_end.x = data->world.waves[i].draw.last_pos.x + data->world.waves[i].draw.last_frame->width;
// 			draw_end.y = data->world.waves[i].draw.last_pos.y +data->world.waves[i].draw.last_frame->height;
// 			restore_background(&data->img_db.background, &data->img_db.saved_background, data->world.waves[i].draw.last_pos, draw_end);
// 		}
// 		i++;
// 	}
// 	if (data->hero.draw.need_redraw)
// 	{
// 		draw_end.x = data->hero.draw.last_pos.x + data->hero.draw.last_frame->width;
// 		draw_end.y = data->hero.draw.last_pos.y + data->hero.draw.last_frame->height;
// 		restore_background(&data->img_db.background, &data->img_db.saved_background, data->hero.draw.last_pos, draw_end);
// 	}
// }

// static void	redraw(t_data *data)
// {
// 	int	i;

// 	if (data->hero.draw.need_redraw)
// 	{
// 		if (data->hero.locomotion.dir < 0)
// 			ft_draw_mirror_to_img(&data->img_db.background, data->hero.draw.frame, data->hero.locomotion.pos.x, data->hero.locomotion.pos.y);
// 		else
// 			ft_draw_img_to_img(&data->img_db.background, data->hero.draw.frame, data->hero.locomotion.pos.x, data->hero.locomotion.pos.y);
// 		data->hero.draw.need_redraw = false;
// 		data->hero.draw.last_frame = data->hero.draw.frame;
// 		data->hero.draw.last_pos = data->hero.locomotion.pos;
// 	}
// 	i = 0;
// 	while (i < 100)
// 	{
// 		if (data->bullets[i].draw.need_redraw)
// 		{
// 			if (data->bullets[i].locomotion.dir < 0)
// 				ft_draw_mirror_to_img(&data->img_db.background, data->bullets[i].draw.frame, data->bullets[i].locomotion.pos.x, data->bullets[i].locomotion.pos.y);
// 			else
// 				ft_draw_img_to_img(&data->img_db.background, data->bullets[i].draw.frame, data->bullets[i].locomotion.pos.x, data->bullets[i].locomotion.pos.y);
// 			data->bullets[i].draw.need_redraw = false;
// 			data->bullets[i].draw.last_frame = data->bullets[i].draw.frame;
// 			data->bullets[i].draw.last_pos = data->bullets[i].locomotion.pos;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (!data->world.waves[i].end)
// 	{
// 		if (data->world.waves[i].draw.need_redraw)
// 		{
// 			ft_draw_img_to_img(&data->img_db.background, data->world.waves[i].draw.frame, data->world.waves[i].pos.x, data->world.waves[i].pos.y);
// 			data->world.waves[i].draw.need_redraw = false;
// 			data->world.waves[i].draw.last_frame = data->world.waves[i].draw.frame;
// 			data->world.waves[i].draw.last_pos = data->world.waves[i].pos;
// 		}
// 		i++;
// 	}
// }

void	render(t_data *data)
{
	restore(data->to_erase, data->nb_to_erase, &data->img_db.background, &data->img_db.saved_background);
	redraw(data->to_draw, data->nb_to_draw, &data->img_db.background);
	// restore(data);
	// redraw(data);
	mlx_put_image_to_window(data->engine.mlx_ptr, data->engine.mlx_win, data->img_db.background.img_ptr, -data->world.camera.x, 0);
	mlx_put_image_to_window(data->engine.mlx_ptr, data->engine.mlx_win, data->img_db.contour.img_ptr, 20, data->world.screen_height - data->img_db.contour.height - 100);

}