/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:39:36 by bvaujour          #+#    #+#             */
/*   Updated: 2024/07/18 00:49:19 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


static void	get_map(t_data *data)
{
	char	*str;
	int		i;
	int		fd;

	i = 0;
	
	fd = secure_open(data, data->paths.path);
	str = get_next_line(fd);
	while (str && ft_strncmp(str, "MAP:", 4) != 0)
	{
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
	{
		secure_close(data, fd);
		quit_error(data, "Missing map");
	}
	free(str);
	str = get_next_line(fd);
	while (str)
	{
		data->world.line_count++;
		free(str);
		str = get_next_line(fd);
	}
	secure_close(data, fd);
	data->world.map = malloc(sizeof(char *) * (data->world.line_count + 1));
	if (!data->world.map)
	{
		secure_close(data, fd);
		quit_error(data, "get_map: Malloc");
	}
	while (i <= data->world.line_count)
	{
		data->world.map[i] = NULL;
		i++;
	}
	i = 0;
	fd = secure_open(data, data->paths.path);
	str = get_next_line(fd);
	while (str && ft_strncmp(str, "MAP:", 4) != 0)
	{
		free(str);
		str = get_next_line(fd);
	}
	if (!str)
	{
		secure_close(data, fd);
		quit_error(data, "Missing map");
	}
	free(str);
	str = get_next_line(fd);
	while (str)
	{
		data->world.map[i] = ft_strtrim(str, "\n", 0);
		if (data->world.line_len != 0 && ft_strlen(data->world.map[i]) != data->world.line_len)
			(free(str), get_next_line(-99), secure_close(data, fd), quit_error(data, "Rectangle"));
		data->world.line_len = ft_strlen(data->world.map[i]);
		i++;
		free (str);
		str = get_next_line(fd);
	}
	data->world.map[i] = NULL;
	secure_close(data, fd);
}

static void	resize_map(t_data *data)
{
	char	**new_map;
	int		new_len;
	int		new_count;
	int		i;
	int		j;
	
	i = 0;
	new_count = data->world.screen_height / data->world.tile_h;
	new_len = data->world.screen_width / data->world.tile_w;
	if (new_len < data->world.line_len)
		new_len = data->world.line_len;
	if (new_count < data->world.line_count)
		new_count = data->world.line_count;
	new_map = malloc(sizeof(char *) * (new_count + 1));
	if (!new_map)
		quit_error(data, "resize_map: Malloc");
	i = new_count;
	new_map[i] = NULL;
	data->world.line_count--;
	i--;
	while (data->world.line_count >= 0)
	{
		new_map[i] = NULL;
		new_map[i] = malloc(sizeof(char) * (new_len + 1));
		if (!new_map[i])
			quit_error(data, "resize_map: Malloc");
		j = 0;
		while (data->world.map[data->world.line_count][j])
		{
			new_map[i][j] = data->world.map[data->world.line_count][j];
			j++;
		}
		while (j < new_len)
		{
			new_map[i][j] = '0';
			j++;
		}
		new_map[i][j] = '\0';
		i--;
		data->world.line_count--;
	}
	while (i >= 0)
	{
		new_map[i] = NULL;
		new_map[i] = malloc(sizeof(char) * (new_len + 1));
		if (!new_map[i])
			quit_error(data, "resize_map: Malloc");
		ft_memset(new_map[i], '0', new_len);
		new_map[i][new_len] = '\0';
		i--;
	}
	ft_freetab((void**)data->world.map);
	data->world.map = new_map;
	data->world.line_len = new_len;
	data->world.line_count = new_count;
}

static void	build_tiles(t_data *data)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == '2')
			{
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Bas, j * data->world.tile_w, i * data->world.tile_h);
				data->world.map[i][j] = 'T';
			}
			else if (data->world.map[i][j] == '5')
			{
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Milieu, j * data->world.tile_w, i * data->world.tile_h);
				data->world.map[i][j] = 'T';
			}
			else if (data->world.map[i][j] == '7')
			{
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_HautG, j * data->world.tile_w, i * data->world.tile_h);
				data->world.map[i][j] = 'T';
			}
			else if (data->world.map[i][j] == '8')
			{
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_Haut, j * data->world.tile_w, i * data->world.tile_h);
				data->world.map[i][j] = 'T';
			}
			else if (data->world.map[i][j] == '9')
			{
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.tile_HautD, j * data->world.tile_w, i * data->world.tile_h);
				data->world.map[i][j] = 'T';
			}
			else if (data->world.map[i][j] == 'E')
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.door, j * data->world.tile_w, (i + 1) * data->world.tile_h - data->img_db.door.height);
			else if (data->world.map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	data->world.animated_tiles = malloc(sizeof(t_animate_tile) * (count + 1));
	count = 0;
	i = 0;
	while (data->world.map[i])
	{
		j = 0;
		while (data->world.map[i][j])
		{
			if (data->world.map[i][j] == 'W')
			{
				init_draw(&data->world.animated_tiles[count].draw, &data->img_db.waves, (t_coor){j * data->world.tile_w, i * data->world.tile_h}, "waves");
				data->world.animated_tiles[count].end = false;
				data->world.animated_tiles[count].pos.x = j * data->world.tile_w;
				data->world.animated_tiles[count].pos.y = i * data->world.tile_h;
				ft_draw_img_to_img(&data->img_db.background, &data->img_db.waves_fix, j * data->world.tile_w, i * data->world.tile_h + data->world.animated_tiles[count].draw.frame->height);
				count++;
			}
			j++;
		}
		i++;
	}
	data->world.animated_tiles[count].end = true;
}

static void	build_map(t_data *data)
{
	int	i;
	int	j;
	t_img	img;
	
	i = 0;
	data->world.map_width = data->world.line_len * data->world.tile_w;
	data->world.map_height = data->world.line_count * data->world.tile_h;
	if (data->world.map_height < data->world.screen_height)
		data->world.map_height = data->world.screen_height;
	if (data->world.map_width < data->world.screen_width)
		data->world.map_width = data->world.screen_width;
	new_empty_img(data, &data->img_db.background, data->world.map_width, data->world.map_height);
	img = ft_new_img_xpm_scaled(&data->engine, data->engine.screen_w, data->engine.screen_h, data->paths.sky);
	j = 0;
	while (j < data->world.map_height / 2 - img.height)
	{
		i = 0;
		while (i < data->world.map_width)
		{
			ft_draw_img_to_img(&data->img_db.background, &img, i, j);
			i += img.width;
		}
		j += img.height;
		
	}
	mlx_destroy_image(data->engine.mlx_ptr, img.img_ptr);
	img = ft_new_img_xpm_scaled(&data->engine, data->engine.screen_w, data->engine.screen_h, data->paths.background);
	i = 0;
	while (i < data->world.map_width)
	{
		ft_draw_img_to_img(&data->img_db.background, &img, i, j);
		i += img.width;
	}
	j += img.height;
	mlx_destroy_image(data->engine.mlx_ptr, img.img_ptr);
	img = ft_new_img_xpm_scaled(&data->engine, data->engine.screen_w, data->engine.screen_h, data->paths.ground);
	while (j < data->world.map_height)
	{
		i = 0;
		while (i < data->img_db.background.width)
		{
			ft_draw_img_to_img(&data->img_db.background, &img, i, j);
			i += img.width;
		}
		j += img.height;
		
	}
	mlx_destroy_image(data->engine.mlx_ptr, img.img_ptr);
}

void	get_infos(t_data *data)
{
	char	*str;
	int		fd;

	fd = secure_open(data, data->paths.path);
	str = get_next_line(fd);
	while (str || (!data->paths.door || !data->paths.next_path || !data->paths.tile_b || !data->paths.tile_h || !data->paths.tile_hd || !data->paths.tile_hg || !data->paths.tile_m || !data->paths.background || !data->paths.sky || !data->paths.ground))
	{
		if (ft_strncmp(str, "NEXT_PATH:", 10) == 0)
			data->paths.next_path = ft_strtrim(str, "NEXT_PATH: \n", 0);
		else if (ft_strncmp(str, "TILE_B:", 7) == 0)
			data->paths.tile_b = ft_strtrim(str, "TILE_B: \n", 0);
		else if (ft_strncmp(str, "TILE_H:", 7) == 0)
			data->paths.tile_h = ft_strtrim(str, "TILE_H: \n", 0);
		else if (ft_strncmp(str, "TILE_HG:", 8) == 0)
			data->paths.tile_hg = ft_strtrim(str, "TILE_HG: \n", 0);
		else if (ft_strncmp(str, "TILE_HD:", 8) == 0)
			data->paths.tile_hd = ft_strtrim(str, "TILE_HD: \n", 0);
		else if (ft_strncmp(str, "TILE_M:", 7) == 0)
			data->paths.tile_m = ft_strtrim(str, "TILE_M: \n", 0);
		else if (ft_strncmp(str, "DOOR:", 5) == 0)
			data->paths.door = ft_strtrim(str, "DOOR: \n", 0);
		else if (ft_strncmp(str, "GROUND:", 7) == 0)
			data->paths.ground = ft_strtrim(str, "GROUND: \n", 0);
		else if (ft_strncmp(str, "BACKGROUND:", 11) == 0)
			data->paths.background = ft_strtrim(str, "BACKGROUND: \n", 0);
		else if (ft_strncmp(str, "SKY:", 4) == 0)
			data->paths.sky = ft_strtrim(str, "SKY: \n", 0);
		free(str);
		str = get_next_line(fd);
	}
	secure_close(data, fd);
}

void	ft_printab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	map_handle(t_data *data)
{

	free(data->paths.path);
	data->paths.path = ft_strdup(data->paths.next_path);
	free(data->paths.next_path);
	data->paths.next_path = NULL;
	get_infos(data);
	data->img_db.tile_Bas = ft_new_img(data, data->paths.tile_b);
	data->img_db.tile_Haut = ft_new_img(data, data->paths.tile_h);
	data->img_db.tile_HautG = ft_new_img(data, data->paths.tile_hg);
	data->img_db.tile_HautD = ft_new_img(data, data->paths.tile_hd);
	data->img_db.tile_Milieu = ft_new_img(data, data->paths.tile_m);
	data->img_db.door = ft_new_img(data, data->paths.door);
	data->world.tile_w = data->img_db.tile_Milieu.width;
	data->world.tile_h = data->img_db.tile_Milieu.height;
	get_map(data);
	ft_printab(data->world.map);
	resize_map(data);
	build_map(data);
	build_tiles(data);
	new_empty_img(data, &data->img_db.saved_background, data->img_db.background.width, data->img_db.background.height);
	ft_draw_img_to_img(&data->img_db.saved_background, &data->img_db.background, 0, 0);
}