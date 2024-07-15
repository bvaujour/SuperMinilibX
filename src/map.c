/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:39:36 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/15 00:26:07 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


static void	get_map(t_data *data, char *path)
{
	int		len;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	len = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		quit(data);
	str = get_next_line(fd);
	while (str)
	{
		len++;
		free(str);
		str = get_next_line(fd);
	}
	close (fd);
	data->world.map = malloc(sizeof(char *) * (len + 1));
	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		data->world.map[i] = ft_strtrim(str, "\n", 0);
		i++;
		free (str);
		str = get_next_line(fd);
	}
	data->world.map[i] = NULL;
	close (fd);
}

static void	build_map(t_data *data)
{
	int	i;
	int	j;
	int	count;
	t_img	img;
	
	i = 0;
	count = 0;
	img = ft_new_img_xpm_scaled(&data->engine, data->engine.screen_w, data->engine.screen_h, "textures/Backgrounds/BG_Forest.xpm");
	data->world.map_width = ft_strlen(data->world.map[0]) * data->img_db.tile_Milieu.width;
	new_empty_img(data, &data->img_db.background, data->world.map_width, data->engine.screen_h);
	while (i < data->img_db.background.width)
	{
		ft_draw_img_to_img(&data->img_db.background, &img, i, 0);
		i += img.width;
	}
	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == '2')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Bas, j * data->img_db.tile_Bas.width, i * data->img_db.tile_Bas.height);
			else if (data->world.map[i][j] == '5')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Milieu, j * data->img_db.tile_Milieu.width, i * data->img_db.tile_Milieu.height);
			else if (data->world.map[i][j] == '7')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_HautG, j * data->img_db.tile_HautD.width, i * data->img_db.tile_HautD.height);
			else if (data->world.map[i][j] == '8')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Haut, j * data->img_db.tile_HautG.width, i * data->img_db.tile_HautG.height);
			else if (data->world.map[i][j] == '9')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_HautD, j * data->img_db.tile_Haut.width, i * data->img_db.tile_Haut.height);
			else if (data->world.map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	data->world.waves = malloc(sizeof(t_animate_tile) * (count + 1));
	count = 0;
	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == 'W')
			{
				init_draw(&data->world.waves[count].draw, &data->img_db.waves, (t_coor){j * data->img_db.waves.img->width, i * data->img_db.waves.img->height});
				data->world.waves[count].end = false;
				data->world.waves[count].pos.x = j * data->img_db.waves.img->width;
				data->world.waves[count].pos.y = i * data->img_db.waves.img->height;
				count++;
			}
			j++;
		}
		i++;
	}
	data->world.waves[count].end = true;
	mlx_destroy_image(data->engine.mlx_ptr, img.img_ptr);
}

void	map_handle(t_data *data, char *path)
{
	get_map(data, path);
	build_map(data);
	new_empty_img(data, &data->img_db.saved_background, data->img_db.background.width, data->img_db.background.height);
	ft_draw_img_to_img(&data->img_db.saved_background, &data->img_db.background, 0, 0);
}