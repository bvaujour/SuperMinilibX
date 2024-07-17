/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:33:25 by vanitas           #+#    #+#             */
/*   Updated: 2024/07/18 00:47:35 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


int		frame(t_data *data)
{
	static time_t last_update	= 0;
	static time_t exec_time		= 0;

	if (gettime() - last_update > 1000 / (data->fps + 5 * exec_time))
	{
		exec_time = gettime();
		show_fps();
		data->nb_to_draw = 0;
		data->nb_to_erase = 0;
		if (data->hero.is_attacking == true)
			character_fire(&data->hero, data->bullets, data->muzzles);
		if (data->hero.is_sprinting == true)
			character_sprint(&data->hero, 0.05);
		else
			character_sprint(&data->hero, -0.1);

		update(data);
		render(data);
		last_update = gettime();
		exec_time = gettime() - exec_time;
		if (collision(&data->world, data->hero.locomotion.root) == EXIT)
		{
			free_reusable_data(data);
			init_values(data);
			map_handle(data);
		}
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
	mlx_do_key_autorepeatoff(data.engine.mlx_ptr);
	mlx_get_screen_size(data.engine.mlx_ptr, &data.engine.screen_w, &data.engine.screen_h);
	data.world.screen_width = data.engine.screen_w;
	data.world.screen_height = data.engine.screen_h;
	data.engine.mlx_win = mlx_new_window(data.engine.mlx_ptr, data.engine.screen_w, data.engine.screen_h, "engine_engine");
	if (!data.engine.mlx_win)
		return (dprintf(2, "ft_power_on: error engine_win\n"), 2);
	data.paths.next_path = NULL;
	init(&data);
	data.paths.next_path = ft_strdup(av[1]);
	map_handle(&data);
	mlx_hook(data.engine.mlx_win, 4, 1L<<2, button_press, &data);
	mlx_hook(data.engine.mlx_win, 5, 1L<<3, button_release, &data);
	mlx_hook(data.engine.mlx_win, 2, 1L<<0, key_press, &data);
	mlx_hook(data.engine.mlx_win, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.engine.mlx_ptr, &frame, &data);
	mlx_loop(data.engine.mlx_ptr);
	return (0);
}
