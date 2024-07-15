/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:33:25 by vanitas           #+#    #+#             */
/*   Updated: 2024/07/15 03:38:04 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


int		frame(t_data *data)
{
	static time_t last_update = 0;

	if (gettime() - last_update > 1000 / data->fps)
	{
		show_fps();
		data->nb_to_draw = 0;
		data->nb_to_erase = 0;
		if (data->hero.is_attacking == true)
			character_fire(&data->hero, data->bullets);
		if (data->hero.is_sprinting == true)
			character_sprint(&data->hero, 0.1);
		else
			character_sprint(&data->hero, -0.1);

		update(data);
		if (data->hero.draw.need_redraw == true)
		{
			data->hero.draw.dir = data->hero.locomotion.dir;
			data->hero.draw.pos = data->hero.locomotion.pos;
			add_to_draw_list(data, &data->hero.draw);
			add_to_erase_list(data, &data->hero.draw);
		}
		render(data);
		last_update = gettime();
	}
	return (0);
}


int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	
	if (ac != 2)
		return 0;
	t_data data;

	data.fps = 60;
	data.engine.mlx_ptr = NULL;
	data.engine.mlx_ptr = mlx_init();
	if (!data.engine.mlx_ptr)
		return (dprintf(2, "ft_power_on: error engine_init\n"), 1);
	mlx_get_screen_size(data.engine.mlx_ptr, &data.engine.screen_w, &data.engine.screen_h);
	data.world.screen_width = data.engine.screen_w;
	data.world.screen_height = data.engine.screen_h;
	data.engine.mlx_win = mlx_new_window(data.engine.mlx_ptr, data.engine.screen_w, data.engine.screen_h, "engine_engine");
	if (!data.engine.mlx_win)
		return (dprintf(2, "ft_power_on: error engine_win\n"), 2);
	init(&data);
	mlx_do_key_autorepeatoff(data.engine.mlx_ptr);
	map_handle(&data, av[1]);
	mlx_hook(data.engine.mlx_win, 4, 1L<<2, button_press, &data);
	mlx_hook(data.engine.mlx_win, 5, 1L<<3, button_release, &data);
	mlx_hook(data.engine.mlx_win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.engine.mlx_win, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.engine.mlx_ptr, &frame, &data);
	mlx_loop(data.engine.mlx_ptr);
	return (0);
}
