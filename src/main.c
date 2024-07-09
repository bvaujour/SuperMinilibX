/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:33:25 by vanitas           #+#    #+#             */
/*   Updated: 2024/07/09 23:07:02 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/game.h"


#define GRAVITY 9.8 // Accélération due à la gravité
#define INITIAL_JUMP_VELOCITY 10 // Vitesse initiale du saut
#define TIME_STEP 0.1 // Pas de temps pour la simulation

// Fonction pour mettre à jour la position du joueur
void update(t_info *player) 
{
	static int save = 0;
	static bool token = true;
	static float i = 1.5;
	int jump = -7;

	if (token == true)
	{
		save = player->pos_y;
		token = false;
	}
	player->pos_y = player->pos_y + jump * i + 0.5 * i * i;
	i += 1;
	if (player->pos_y > save)
	{
		player->is_jumping = false;
		token = true;
		player->pos_y = save;
		save = 0;
		i = 1.5;
	}
}

void	quit(t_data *data)
{
	mlx_destroy_image(data->engine.mlx_ptr, data->hero.img_ptr);
	mlx_destroy_window(data->engine.mlx_ptr, data->engine.mlx_win);
	mlx_destroy_display(data->engine.mlx_ptr);
	free(data->engine.mlx_ptr);
	exit(0);
}
int	key_handle(int keypress, t_data *data)
{
	(void)data;
	printf("%d\n", keypress);
	if (keypress == 65307)
		quit(data);
	if (keypress == 32)
		data->hero_info.is_jumping = true;
	return (0);
}

int	render(t_data *data)
{
	mlx_clear_window(data->engine.mlx_ptr, data->engine.mlx_win);
	if (data->hero_info.is_jumping == true)
		update(&data->hero_info);
	mlx_put_image_to_window(data->engine.mlx_ptr, data->engine.mlx_win, data->hero.img_ptr, data->hero_info.pos_x, data->hero_info.pos_y);
	usleep(50000);
	return (0);
}
int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	
	t_data data;
	ft_power_on(&data.engine, 1400, 900);
	
	data.hero_info.pos_x = 400;
	data.hero_info.pos_y = 400;
	data.hero = ft_new_img_xpm(&data.engine, "textures/robotfree/xpm/Jump (1).xpm");
	mlx_hook(data.engine.mlx_win, 2, 1L<<0, &key_handle, &data);
	mlx_loop_hook(data.engine.mlx_ptr, &render, &data);
	mlx_loop(data.engine.mlx_ptr);
	return (0);
}
