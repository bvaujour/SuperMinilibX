/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:59:38 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 03:43:38 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"

void	show_fps()
{
	static time_t	last_save = 0;
	static int		count = 0;

	if (gettime() - last_save > 1000)
	{
		last_save = gettime();
		printf ("fps = %d\n", count);
		count = 0;
	}
	count++;
}

time_t	gettime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	new_empty_img(t_data *data, t_img *image, int width, int height)
{
	ft_init_img_clean(image);
	image->img_ptr = mlx_new_image(data->engine.mlx_ptr, width, height);
	if (image->img_ptr == NULL)
		quit(data);
	image->addr = (int *)mlx_get_data_addr(image->img_ptr,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->width = width;
	image->height = height;
	return ;
}

void		add_to_draw_list(t_data *data, t_draw *to_draw)
{
	if (data->nb_to_draw < 150)
	{
		to_draw->need_redraw = true;
		data->to_draw[data->nb_to_draw] = to_draw;
		data->nb_to_draw++;
	}
}

void		add_to_erase_list(t_data *data, t_draw *to_erase)
{
	if (data->nb_to_erase < 150)
	{
		data->to_erase[data->nb_to_erase] = to_erase;
		data->nb_to_erase++;
	}
}
