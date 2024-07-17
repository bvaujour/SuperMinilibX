/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:59:38 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/17 23:21:15 by bvaujour         ###   ########.fr       */
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
		quit_error(data, "new empty img");
	image->addr = (int *)mlx_get_data_addr(image->img_ptr,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	image->width = width;
	image->height = height;
	return ;
}

void	add_to_draw_list(t_data *data, t_draw *to_draw)
{
	int max;

	max = data->stock;
	if (data->nb_to_draw < max)
	{
		to_draw->need_redraw = true;
		data->to_draw[data->nb_to_draw] = to_draw;
		data->nb_to_draw++;
	}
}

void	add_to_erase_list(t_data *data, t_draw *to_erase)
{
	int max;

	max = data->stock;
	if (data->nb_to_erase < max)
	{
		data->to_erase[data->nb_to_erase] = to_erase;
		data->nb_to_erase++;
	}
}


bool	is_in_screen(t_world *world, t_img *img, t_coor pos)
{
	if (pos.x + img->width < world->camera.x)
		return (0);
	else if (pos.x > world->camera.x + world->screen_width)
		return (0);
	return (1);
}

e_case	collision(t_world *world, t_coor root)
{
	char case_map;

	if (root.y < 0 || root.x < 0 || root.y >= world->map_height || root.x >= world->map_width)
		return (OUT);
	case_map = world->map[root.y / world->tile_h][root.x / world->tile_w];
	if (case_map == 'E')
		return (EXIT);
	if (case_map == 'W')
		return (WATER);
	if (case_map == 'T')
		return (TILE);
	return (AIR);
}

int	secure_open(t_data *data, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		quit_error(data, "open");
	return (fd);
}

void	secure_close(t_data *data, int fd)
{
	if (close(fd) == -1)
		quit_error(data, "close");
}
