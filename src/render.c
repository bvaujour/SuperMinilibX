/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:43:45 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 13:55:06 by bvaujour         ###   ########.fr       */
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

	// printf("erase list:\n");
	while (i < nb)
	{
		// printf("%s\n", to_erase[i]->name);
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

	// printf("draw list:\n");
	while (i < nb)
	{
		// printf("%s\n", to_draw[i]->name);
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

void	render(t_data *data)
{
	restore(data->to_erase, data->nb_to_erase, &data->img_db.background, &data->img_db.saved_background);
	redraw(data->to_draw, data->nb_to_draw, &data->img_db.background);
	mlx_put_image_to_window(data->engine.mlx_ptr, data->engine.mlx_win, data->img_db.background.img_ptr, -data->world.camera.x, 0);
	mlx_put_image_to_window(data->engine.mlx_ptr, data->engine.mlx_win, data->img_db.contour.img_ptr, 20, data->world.screen_height - data->img_db.contour.height - 100);

}